#include "/usr/include/minilibx-linux/mlx.h"
#include "string.h"
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define WALL_XPM "sprites/wall.xpm"
#define FLOOR_XPM "sprites/floor.xpm"
#define COLL_XPM "sprites/coin-bag.xpm"
#define FRONT_XPM "sprites/player/front.xpm"
#define LEFT_XPM "sprites/player/left.xpm"
#define RIGHT_XPM "sprites/player/right.xpm"
#define BACK_XPM "sprites/player/back.xpm"
#define OPEN_EXIT_XPM "sprites/open-exit.xpm"
#define EXIT_XPM "sprites/exit-closed.xpm"

#include <math.h>

#define PI 3.14159265359
#define MAP_ROW 14
#define MAP_COL 12
#define TILE_SIZE 32
#define WIN_WIDTH 1920 
#define WIN_HEIGHT 1080 
#define MAX_RAY_LENGTH 200

// Minimap settings
#define MINIMAP_SCALE 8  // Each tile will be 8x8 pixels
#define MINIMAP_X 20     // X position of minimap
#define MINIMAP_Y 20     // Y position of minimap

typedef struct s_intersection
{
	bool is_vert;
	int x;
	int y;
	double distance;

} t_intersection;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;

    int px, py;         // player pixel coordinates
    double angle;       // player direction
    int x, y;           // player tile coordinates

    char **map;
} t_game;

double normalize(double angle)
{
    angle = fmod(angle , (2 * PI));
    if (angle < 0)
        angle = angle + (2 * PI);
    return angle;
}

void my_pixel_put(t_game *g, int x, int y, int color)
{
    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;

    char *dst = g->addr + (y * g->line_length + x * (g->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void draw_map(t_game *g)
{
    for (int i = 0; i < WIN_HEIGHT; i++)
    {
        for (int j = 0; j < WIN_WIDTH ; j++)
        {
		if (i < WIN_HEIGHT / 2)
			my_pixel_put(g, j,i , 0x87CEEB); // Sky blue
		else 
			my_pixel_put(g, j, i , 0x2F4F4F); // Dark gray floor
        }
    }
}

void draw_minimap(t_game *g)
{
    // Draw map tiles
    for (int y = 0; y < MAP_ROW; y++)
    {
        for (int x = 0; x < MAP_COL; x++)
        {
            int color;
            if (g->map[y][x] == '1')
                color = 0x000000; // Black for walls
            else
                color = 0xFFFFFF; // White for floor
            
            // Draw tile
            for (int py = 0; py < MINIMAP_SCALE; py++)
            {
                for (int px = 0; px < MINIMAP_SCALE; px++)
                {
                    my_pixel_put(g, 
                        MINIMAP_X + x * MINIMAP_SCALE + px,
                        MINIMAP_Y + y * MINIMAP_SCALE + py,
                        color);
                }
            }
        }
    }
    
    // Draw player position
    int player_map_x = (g->px / TILE_SIZE) * MINIMAP_SCALE + MINIMAP_X;
    int player_map_y = (g->py / TILE_SIZE) * MINIMAP_SCALE + MINIMAP_Y;
    
    // Draw player as a red circle (simplified as a square)
    for (int py = -2; py <= 2; py++)
    {
        for (int px = -2; px <= 2; px++)
        {
            my_pixel_put(g, player_map_x + px, player_map_y + py, 0xFF0000);
        }
    }
    
    // Draw player direction line
    int line_length = 10;
    for (int i = 0; i < line_length; i++)
    {
        int dx = player_map_x + (int)(cos(g->angle) * i);
        int dy = player_map_y + (int)(sin(g->angle) * i);
        my_pixel_put(g, dx, dy, 0xFFFF00); // Yellow direction line
    }
    
    // Draw border around minimap
    int map_width = MAP_COL * MINIMAP_SCALE;
    int map_height = MAP_ROW * MINIMAP_SCALE;
    
    for (int i = -1; i <= map_width; i++)
    {
        my_pixel_put(g, MINIMAP_X + i, MINIMAP_Y - 1, 0xFFFFFF);
        my_pixel_put(g, MINIMAP_X + i, MINIMAP_Y + map_height, 0xFFFFFF);
    }
    for (int i = -1; i <= map_height; i++)
    {
        my_pixel_put(g, MINIMAP_X - 1, MINIMAP_Y + i, 0xFFFFFF);
        my_pixel_put(g, MINIMAP_X + map_width, MINIMAP_Y + i, 0xFFFFFF);
    }
}

#define NUM_RAYS WIN_WIDTH
#define FOV (M_PI / 3) // 60 degrees

int is_wall(t_game *g, int px, int py)
{
    int tile_x = px / TILE_SIZE;
    int tile_y = py / TILE_SIZE;

    if (tile_x < 0 || tile_x >= MAP_COL || tile_y < 0 || tile_y >= MAP_ROW)
        return 1; // outside map = wall

    return (g->map[tile_y][tile_x] == '1');
}


int istherewall(t_game *g, double x, double y)
{
    int xx = x / TILE_SIZE;
    int yy = y / TILE_SIZE;

    if (xx < 0 || yy < 0)
        return 1;
    if (yy >= MAP_COL || xx >= MAP_ROW) 
        return 1;

    return (g->map[yy][xx] == '1'); // FIXED
}

double distancebetwen2points(int x1, int y1, int x2, int y2)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

int is_ray_facing_down(double ray_angle)
{
    return (ray_angle > 0 && ray_angle < PI);
}

int is_ray_facing_up(double ray_angle)
{
    return (!is_ray_facing_down(ray_angle));
}

int is_ray_facing_right(double ray_angle)
{
    return (ray_angle < PI * 0.5 || ray_angle > PI * 1.5);
}

int is_ray_facing_left(double ray_angle)
{
    return (!is_ray_facing_right(ray_angle));
}

t_intersection *verticaldist(t_game *g, double ray_angle)
{
	double x_intercept;
	double y_intercept;
	double x_step;
	double y_step;
	t_intersection *inter;

	inter = malloc(sizeof(t_intersection));
	x_intercept = floor(g->px / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		x_intercept += TILE_SIZE;
	y_intercept = g->py + (x_intercept - g->px) * tan(ray_angle);
	x_step = TILE_SIZE;
	if (is_ray_facing_left(ray_angle))
		x_step = -TILE_SIZE;
	y_step = TILE_SIZE * tan(ray_angle);
	if (is_ray_facing_up(ray_angle) && y_step > 0)
		y_step = -y_step;
	if (is_ray_facing_down(ray_angle) && y_step < 0)
		y_step = -y_step;
	if (is_ray_facing_left(ray_angle))
		x_intercept -= 0.0001;
	while (!istherewall(g, x_intercept, y_intercept))
	{
		x_intercept += x_step;
		y_intercept += y_step;
	}
	inter->x = x_intercept;
	inter->y = y_intercept;
	inter->distance = distancebetwen2points(g->px, g->py, x_intercept, y_intercept);
	return inter;
}

t_intersection *horizontaldist(t_game *g, double ray_angle)
{
	double x_intercept;
	double y_intercept;
	double x_step;
	double y_step;
	t_intersection *inter;

	inter = malloc(sizeof(t_intersection));
	y_intercept= floor(g->py / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		y_intercept += TILE_SIZE;
	x_intercept = g->px + (y_intercept - g->py) / tan(ray_angle);
	y_step = TILE_SIZE;
	if (is_ray_facing_up(ray_angle))
		y_step *= -1;
	x_step = TILE_SIZE / tan(ray_angle);
	if (is_ray_facing_left(ray_angle) && x_step > 0)
		x_step = -x_step;
	if (is_ray_facing_right(ray_angle) && x_step < 0)
		x_step = -x_step;
	if (is_ray_facing_up(ray_angle))
		y_intercept -= 0.0001;
	while (!istherewall(g, x_intercept, y_intercept))
	{
		x_intercept += x_step;
		y_intercept += y_step;
	}
	inter->x = x_intercept;
	inter->y = y_intercept;
	inter->distance = distancebetwen2points(g->px, g->py, x_intercept, y_intercept);
	return inter;
}

t_intersection *ray(t_game *g, double rayAngle)
{
	rayAngle = normalize(rayAngle);

	t_intersection *v_inter = verticaldist(g, rayAngle);
	t_intersection *h_inter = horizontaldist(g, rayAngle);


	if (v_inter->distance < h_inter->distance)
	{
		v_inter->is_vert = true;
		free(h_inter);
		return v_inter;
	}
	h_inter->is_vert = false;
	free(v_inter);
	return h_inter;
}

#define DIS_PROJ_PLAYER 1500

void release_rays(t_game *game, t_intersection *inter)
{
    double start_ray = game->angle - (FOV/2);
    start_ray = normalize(start_ray);
    double wall_strip_height;
    double wall_top;
    double wall_bottom;
    

    wall_strip_height = 0;
    double angle_step = FOV / NUM_RAYS;
    int h = (WIN_WIDTH / 2) / (FOV / 2);
    for (int i = 0; i < NUM_RAYS; i++)
    {
	t_intersection *inter = ray(game, start_ray);
	double dist = cos(start_ray - game->angle) * inter->distance;
	wall_strip_height = h / dist;
	wall_top = (WIN_HEIGHT / 2) - (wall_strip_height / 2);	
	if (wall_top < 0)
		wall_top = 0;
	wall_bottom = (WIN_HEIGHT / 2) + (wall_strip_height / 2);	
	if (wall_bottom > WIN_HEIGHT)
		wall_bottom = WIN_HEIGHT;
	
	// Different colors for horizontal and vertical walls
	int wall_color = inter->is_vert ? 0x008000 : 0x006400;
	
	for (int j = wall_top; j < wall_bottom;j++)
	{
		my_pixel_put(game, i, j, wall_color);
	}
	free(inter);
	start_ray += angle_step;
    }
}

void render(t_game *g)
{
	t_intersection *inter = malloc(sizeof(t_intersection) * NUM_RAYS);	

	draw_map(g);
	release_rays(g, inter);
	draw_minimap(g);  // Draw minimap on top
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	free(inter);
}



int handle_input(int key, t_game *g)
{
    double move_speed = 5;
    double rot_speed = 0.1;

    g->angle = normalize(g->angle);
    if (key == 65307) // ESC
        exit(0);
    if (key == 97 || key == XK_Left) // A / Left arrow - rotate left
        g->angle -= rot_speed;
    if (key == 100 || key == XK_Right) // D / Right arrow - rotate right
        g->angle += rot_speed;
    if (key == 119 || key == XK_Down) // W
    {
        int new_px = g->px + cos(g->angle) * move_speed;
        int new_py = g->py + sin(g->angle) * move_speed;
        if (!is_wall(g, new_px, g->py))
            g->px = new_px;
        if (!is_wall(g, g->px, new_py))
            g->py = new_py;
    }
    if (key == 115 || key == XK_Up) // S
    {
        int new_px = g->px - cos(g->angle) * move_speed;
        int new_py = g->py - sin(g->angle) * move_speed;

        if (!is_wall(g, new_px, g->py))
            g->px = new_px;
        if (!is_wall(g, g->px, new_py))
            g->py = new_py;
    }
    render(g);
    return 0;
}

int main()
{
    t_game *g = malloc(sizeof(t_game));

    g->mlx = mlx_init();
    g->win = mlx_new_window(g->mlx, WIN_WIDTH, WIN_HEIGHT, "Player Ray Demo");
    g->img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
    g->addr = mlx_get_data_addr(g->img, &g->bits_per_pixel, &g->line_length, &g->endian);

    g->x = 7; g->y = 5;
    g->px = g->x * TILE_SIZE + TILE_SIZE;
    g->py = g->y * TILE_SIZE + TILE_SIZE;
    g->angle = 0; // facing right

    // Map
    g->map = malloc(sizeof(char*) * 14);
    g->map[0] = "111111111111";
    g->map[1] = "100010000001";
    g->map[2] = "100010000001";
    g->map[3] = "100111000001";
    g->map[4] = "100000000001";
    g->map[5] = "100000000001";
    g->map[6] = "101110000001";
    g->map[7] = "100011000001";
    g->map[8] = "100011100001";
    g->map[9] = "111111111101";
    g->map[10] = "111111111101";
    g->map[11] = "111111111111";
    g->map[12] = "111111111111";
    g->map[13] = "111111111111";

    render(g);

    mlx_hook(g->win, 2, 1L << 0, handle_input, g); // key press
    mlx_loop(g->mlx);

    return 0;
}
