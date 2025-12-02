#include "/usr/include/minilibx-linux/mlx.h"
#include "string.h"
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

#define MAP_ROW 14
#define MAP_COL 12
#define TILE_SIZE 32
#define WIN_WIDTH (MAP_COL * TILE_SIZE)
#define WIN_HEIGHT (MAP_ROW * TILE_SIZE)
#define MAX_RAY_LENGTH 200

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

// Draw a pixel into the image
void my_pixel_put(t_game *g, int x, int y, int color)
{
    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;

    char *dst = g->addr + (y * g->line_length + x * (g->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

// Draw the map tiles into the image
void draw_map(t_game *g)
{
    for (int i = 0; i < MAP_ROW; i++)
    {
        for (int j = 0; j < MAP_COL; j++)
        {
            int color = (g->map[i][j] == '1') ? 0x00FF0000 : 0x00000000;
            for (int y = 0; y < TILE_SIZE; y++)
            {
                for (int x = 0; x < TILE_SIZE; x++)
                {
                    my_pixel_put(g, j * TILE_SIZE + x, i * TILE_SIZE + y, color);
                }
            }
        }
    }
}

// Draw a filled circle for the player
void draw_player(t_game *g)
{
    int radius = TILE_SIZE / 2;
    int cx = g->px;
    int cy = g->py;

    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            if (x*x + y*y <= radius*radius)
                my_pixel_put(g, cx + x, cy + y, 0x008000); // green
        }
    }
}

// Bresenham line

#define NUM_RAYS 120
#define FOV (M_PI / 3) // 60 degrees




int is_wall(t_game *g, int px, int py)
{
    int tile_x = px / TILE_SIZE;
    int tile_y = py / TILE_SIZE;

    if (tile_x < 0 || tile_x >= MAP_COL || tile_y < 0 || tile_y >= MAP_ROW)
        return 1; // outside map = wall

    return (g->map[tile_y][tile_x] == '1');
}

void draw_ray(t_game *game, double x0, double y0, double x1, double y1)
{
    double dx = x1 - x0;
    double dy = y1 - y0;
    double steps = fmax(fabs(dx), fabs(dy));
    double step_x = dx / steps;
    double step_y = dy / steps;

    double px = x0;
    double py = y0;

    for (int i = 0; i < steps; i++)
    {
        my_pixel_put(game, (int)px, (int)py, 0x00FF00);
        px += step_x;
        py += step_y;
    }
}

void draw_line(t_game *g, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        my_pixel_put(g, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void    ray(t_game *g, double rayAngle)
{
    double len_ray = 20000;

    int rx = g->px + cos(rayAngle) * len_ray;
    int ry = g->py + sin(rayAngle) * len_ray;
    draw_line(g, g->px, g->py, rx, ry, 0x008000);
}

void release_rays(t_game *game)
{
    double start_ray = game->angle - (FOV/2);
    int coulm = 0;

    for (int i = 0; i < NUM_RAYS; i++)
    {
        ray(game, start_ray);
        coulm++;
        start_ray += FOV / NUM_RAYS;
    }
}


void render(t_game *g)
{
    draw_map(g);
    draw_player(g);
    release_rays(g);    
    mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}


int handle_input(int key, t_game *g)
{
    double move_speed = 5;
    double rot_speed = 0.1;

    if (key == 65307) // ESC
        exit(0);
    if (key == 97 || key == 65361) // A / Left arrow - rotate left
        g->angle -= rot_speed;
    if (key == 100 || key == 65363) // D / Right arrow - rotate right
        g->angle += rot_speed;
    if (key == 119 || key == 65362) // W
    {
        printf("cos[angle] = %f\n", cos(g->angle));
        printf("sin[angle] = %f\n", sin(g->angle));
        int new_px = g->px + cos(g->angle) * move_speed;
        int new_py = g->py + sin(g->angle) * move_speed;
        if (!is_wall(g, new_px, g->py))
            g->px = new_px;
        if (!is_wall(g, g->px, new_py))
            g->py = new_py;
    }
    if (key == 115 || key == 65364) // S
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

int main(void)
{
    t_game *g = malloc(sizeof(t_game));

    g->mlx = mlx_init();
    g->win = mlx_new_window(g->mlx, WIN_WIDTH, WIN_HEIGHT, "Player Ray Demo");
    g->img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
    g->addr = mlx_get_data_addr(g->img, &g->bits_per_pixel, &g->line_length, &g->endian);

    g->x = 7; g->y = 5;
    g->px = g->x * TILE_SIZE + TILE_SIZE/2;
    g->py = g->y * TILE_SIZE + TILE_SIZE/2;
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
