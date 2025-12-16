#include "cub3d.h"

void draw_minimap(t_game *g)
{
    // Draw map tiles
    for (int y = 0; y < g->data->hight; y++)
    {
        for (int x = 0; x < g->data->hight; x++)
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
    int player_map_x = (g->px / TILE_SIZE) * MINIMAP_SCALE + MINIMAP_X;
    int player_map_y = (g->py / TILE_SIZE) * MINIMAP_SCALE + MINIMAP_Y;
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
    int map_width = g->data->hight * MINIMAP_SCALE;
    int map_height = g->data->width * MINIMAP_SCALE;
    
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
        inter = ray(game, start_ray);
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
            my_pixel_put(game, i, j, wall_color);
        start_ray += angle_step;
        free(inter);
    }
}

void render(t_game *g)
{
	t_intersection *inter = malloc(sizeof(t_intersection) * NUM_RAYS);	

	draw_map(g);
	release_rays(g, inter);
	draw_minimap(g);  
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
        if (!istherewall(g, new_px, g->py))
            g->px = new_px;
        if (!istherewall(g, g->px, new_py))
            g->py = new_py;
    }
    if (key == 115 || key == XK_Up) // S
    {
        int new_px = g->px - cos(g->angle) * move_speed;
        int new_py = g->py - sin(g->angle) * move_speed;

        if (!istherewall(g, new_px, g->py))
            g->px = new_px;
        if (!istherewall(g, g->px, new_py))
            g->py = new_py;
    }
    render(g);
    return 0;
}

void	cub3d(t_data *data)
{
	t_game *g = malloc(sizeof(t_game));

	g->data = data;
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, WIN_WIDTH, WIN_HEIGHT, "Player Ray Demo");
	g->img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	g->addr = mlx_get_data_addr(g->img, &g->bits_per_pixel, &g->line_length, &g->endian);


	g->map = data->map;
	g->x = data->x;
	g->y = data->y;
	g->px = data->x * TILE_SIZE + TILE_SIZE;
	g->py = data->y * TILE_SIZE + TILE_SIZE;
	g->angle = 0; // facing right

	render(g);

	mlx_hook(g->win, 2, 1L << 0, handle_input, g); // key press
	mlx_loop(g->mlx);
	mlx_destroy_display(g->mlx);
	mlx_destroy_window(g->mlx, g->win);
}

// void    cub3d(t_data *data)
// {
//     t_game *g = malloc(sizeof(t_game));

//     g->data = data;
//     g->mlx = mlx_init();
//     g->win = mlx_new_window(g->mlx, WIN_WIDTH, WIN_HEIGHT, "Player Ray Demo");
//     g->img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
//     g->addr = mlx_get_data_addr(g->img, &g->bits_per_pixel, &g->line_length, &g->endian);

//     g->x = 7; g->y = 5;
//     g->px = g->x * TILE_SIZE + TILE_SIZE;
//     g->py = g->y * TILE_SIZE + TILE_SIZE;
//     g->angle = 0; // facing right

//     // Map
//     g->map = malloc(sizeof(char*) * 14);
//     g->map[0] = "111111111111";
//     g->map[1] = "100010000001";
//     g->map[2] = "100010000001";
//     g->map[3] = "100111000001";
//     g->map[4] = "100000001001";
//     g->map[5] = "100000001001";
//     g->map[6] = "101110000001";
//     g->map[7] = "100011000001";
//     g->map[8] = "100011100001";
//     g->map[9] = "111111111101";
//     g->map[10] = "111111111101";
//     g->map[11] = "111111111111";
//     g->map[12] = "111111111111";
//     g->map[13] = "111111111111";

//     render(g);

//     mlx_hook(g->win, 2, 1L << 0, handle_input, g); // key press
//     mlx_loop(g->mlx);

// }

// #include "cub3d.h"

// void draw_minimap(t_game *g)
// {
//     // Draw map tiles
//     for (int y = 0; y < g->data->hight; y++)
//     {
//         for (int x = 0; x < g->data->width; x++)  // FIXED: was g->data->hight
//         {
//             int color;
//             if (g->map[y][x] == '1')
//                 color = 0x000000; // Black for walls
//             else
//                 color = 0xFFFFFF; // White for floor
            
//             // Draw tile
//             for (int py = 0; py < MINIMAP_SCALE; py++)
//             {
//                 for (int px = 0; px < MINIMAP_SCALE; px++)
//                 {
//                     my_pixel_put(g, 
//                         MINIMAP_X + x * MINIMAP_SCALE + px,
//                         MINIMAP_Y + y * MINIMAP_SCALE + py,
//                         color);
//                 }
//             }
//         }
//     }
//     int player_map_x = (g->px / TILE_SIZE) * MINIMAP_SCALE + MINIMAP_X;
//     int player_map_y = (g->py / TILE_SIZE) * MINIMAP_SCALE + MINIMAP_Y;
//     for (int py = -2; py <= 2; py++)
//     {
//         for (int px = -2; px <= 2; px++)
//         {
//             my_pixel_put(g, player_map_x + px, player_map_y + py, 0xFF0000);
//         }
//     }
    
//     // Draw player direction line
//     int line_length = 10;
//     for (int i = 0; i < line_length; i++)
//     {
//         int dx = player_map_x + (int)(cos(g->angle) * i);
//         int dy = player_map_y + (int)(sin(g->angle) * i);
//         my_pixel_put(g, dx, dy, 0xFFFF00); // Yellow direction line
//     }
    
//     // Draw border around minimap
//     int map_width = g->data->width * MINIMAP_SCALE;  // FIXED: was using hight
//     int map_height = g->data->hight * MINIMAP_SCALE; // FIXED: was using width
    
//     for (int i = -1; i <= map_width; i++)
//     {
//         my_pixel_put(g, MINIMAP_X + i, MINIMAP_Y - 1, 0xFFFFFF);
//         my_pixel_put(g, MINIMAP_X + i, MINIMAP_Y + map_height, 0xFFFFFF);
//     }
//     for (int i = -1; i <= map_height; i++)
//     {
//         my_pixel_put(g, MINIMAP_X - 1, MINIMAP_Y + i, 0xFFFFFF);
//         my_pixel_put(g, MINIMAP_X + map_width, MINIMAP_Y + i, 0xFFFFFF);
//     }
// }

// t_intersection *ray(t_game *g, double rayAngle)
// {
//     rayAngle = normalize(rayAngle);

//     t_intersection *v_inter = verticaldist(g, rayAngle);
//     t_intersection *h_inter = horizontaldist(g, rayAngle);

//     if (v_inter->distance < h_inter->distance)
//     {
//         v_inter->is_vert = true;
//         free(h_inter);
//         return v_inter;
//     }
//     h_inter->is_vert = false;
//     free(v_inter);
//     return h_inter;
// }

// void release_rays(t_game *game)
// {
//     double start_ray = game->angle - (FOV/2);
//     start_ray = normalize(start_ray);
//     double wall_strip_height;
//     double wall_top;
//     double wall_bottom;
    
//     double angle_step = FOV / NUM_RAYS;
//     double h = (WIN_WIDTH / 2.0) / (FOV / 2.0);
    
//     for (int i = 0; i < NUM_RAYS; i++)
//     {
//         t_intersection *inter = ray(game, start_ray);
        
//         if (inter == NULL)
//         {
//             start_ray += angle_step;
//             continue;
//         }
        
//         double dist = cos(start_ray - game->angle) * inter->distance;
        
//         if (dist > 0)
//         {
//             wall_strip_height = h / dist;
//             wall_top = (WIN_HEIGHT / 2.0) - (wall_strip_height / 2.0);	
//             if (wall_top < 0)
//                 wall_top = 0;
//             wall_bottom = (WIN_HEIGHT / 2.0) + (wall_strip_height / 2.0);	
//             if (wall_bottom > WIN_HEIGHT)
//                 wall_bottom = WIN_HEIGHT;
            
//             // Different colors for horizontal and vertical walls
//             int wall_color = inter->is_vert ? 0x008000 : 0x006400;
            
//             for (int j = wall_top; j < wall_bottom; j++)
//                 my_pixel_put(game, i, j, wall_color);
//         }
        
//         free(inter);
//         start_ray += angle_step;
//     }
// }

// void render(t_game *g)
// {
//     draw_map(g);
//     release_rays(g);
//     draw_minimap(g);  
//     mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
// }

// int handle_input(int key, t_game *g)
// {
//     double move_speed = 5;
//     double rot_speed = 0.1;

//     g->angle = normalize(g->angle);
//     if (key == 65307) // ESC
//     {
//         mlx_destroy_window(g->mlx, g->win);
//         exit(0);
//     }
//     if (key == 97 || key == XK_Left) // A / Left arrow - rotate left
//         g->angle -= rot_speed;
//     if (key == 100 || key == XK_Right) // D / Right arrow - rotate right
//         g->angle += rot_speed;
//     if (key == 119 || key == XK_Down) // W
//     {
//         double new_px = g->px + cos(g->angle) * move_speed;
//         double new_py = g->py + sin(g->angle) * move_speed;
//         if (!istherewall(g, new_px, g->py))
//             g->px = new_px;
//         if (!istherewall(g, g->px, new_py))
//             g->py = new_py;
//     }
//     if (key == 115 || key == XK_Up) // S
//     {
//         double new_px = g->px - cos(g->angle) * move_speed;
//         double new_py = g->py - sin(g->angle) * move_speed;

//         if (!istherewall(g, new_px, g->py))
//             g->px = new_px;
//         if (!istherewall(g, g->px, new_py))
//             g->py = new_py;
//     }
//     render(g);
//     return 0;
// }

// void cub3d(t_data *data)
// {
//     t_game *g = malloc(sizeof(t_game));
//     if (!g)
//         return;

//     g->data = data;
//     g->mlx = mlx_init();
//     if (!g->mlx)
//     {
//         free(g);
//         return;
//     }
    
//     g->win = mlx_new_window(g->mlx, WIN_WIDTH, WIN_HEIGHT, "Player Ray Demo");
//     if (!g->win)
//     {
//         free(g);
//         return;
//     }
    
//     g->img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
//     if (!g->img)
//     {
//         mlx_destroy_window(g->mlx, g->win);
//         free(g);
//         return;
//     }
    
//     g->addr = mlx_get_data_addr(g->img, &g->bits_per_pixel, &g->line_length, &g->endian);

//     g->map = data->map;
//     g->x = data->x;
//     g->y = data->y;
//     g->px = data->x * TILE_SIZE + TILE_SIZE / 2;
//     g->py = data->y * TILE_SIZE + TILE_SIZE / 2;
//     g->angle = 0; // facing right

//     render(g);

//     mlx_hook(g->win, 2, 1L << 0, handle_input, g);
//     mlx_loop(g->mlx);
// }