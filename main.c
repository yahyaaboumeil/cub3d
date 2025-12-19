/* file: main.c */
#include "cub3d.h"

int main(int argc, char **argv)
{
    t_data  *data;
    t_game  *g;
    int     i;

    if (argc != 2)
        return (printf("Error\nUsage: ./cub3D <map.cub>\n"), 1);
    data = parsing(argv[1]);
    if (!data)
        return (1);
    g = malloc(sizeof(t_game));
    g->mlx = mlx_init();
    g->map = data->map;
    i = 0;
   
    g->map_rows = data->hight;
    g->floor_color = rgb_to_hex(data->f_color);
    g->ceil_color = rgb_to_hex(data->c_color);
    g->win = mlx_new_window(g->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
    g->img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
    g->addr = mlx_get_data_addr(g->img, &g->bits_per_pixel, 
            &g->line_length, &g->endian);
    load_textures(g, data);
    init_player(g);
    free(data->north_path);
    free(data->south_path);
    free(data->east_path);
    free(data->west_path);
    free(data);
    render(g);
    mlx_hook(g->win, 2, 1L << 0, handle_input, g);
    mlx_hook(g->win, 17, 0, (void*)exit, 0);
    mlx_loop(g->mlx);
    return (0);
}
