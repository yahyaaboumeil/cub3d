/* file: main.c */
#include "cub3d.h"

static void	norm(t_game *g, t_data *data)
{
	g->map_rows = data->hight;
	g->floor_color = rgb_to_hex(data->f_color);
	g->ceil_color = rgb_to_hex(data->c_color);
	g->win = mlx_new_window(g->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	g->img = mlx_new_image(g->mlx, WIN_WIDTH, WIN_HEIGHT);
	g->addr = mlx_get_data_addr(g->img, &g->bits_per_pixel, &g->line_length,
			&g->endian);
	g->tex_e.img = NULL;
	g->tex_n.img = NULL;
	g->tex_s.img = NULL;
	g->tex_w.img = NULL;
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_game	*g;

	if (argc != 2)
		return (printf("Error\nUsage: ./cub3D <map.cub>\n"), 1);
	data = parsing(argv[1]);
	if (!data)
		return (1);
	g = malloc(sizeof(t_game));
	g->mlx = mlx_init();
	g->map = data->map;
	g->data = data;
	norm(g, data);
	load_textures(g, data);
	init_player(g);
	render(g);
	mlx_hook(g->win, 2, 1L << 0, handle_input, g);
	mlx_hook(g->win, 17, 0, (void *)exit, 0);
	mlx_loop(g->mlx);
	clean_all(g, 0);
	return (0);
}
