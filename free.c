#include "cub3d.h"

void	clean_all(t_game *g, int exit_code)
{
	free_memory(g->map);
	if (g->mlx && g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->tex_s.img)
		mlx_destroy_image(g->mlx, g->tex_s.img);
	if (g->tex_n.img)
		mlx_destroy_image(g->mlx, g->tex_n.img);
	if (g->tex_w.img)
		mlx_destroy_image(g->mlx, g->tex_w.img);
	if (g->tex_e.img)
		mlx_destroy_image(g->mlx, g->tex_e.img);
	if (g->img)
		mlx_destroy_image(g->mlx, g->img);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	free(g->data->east_path);
	free(g->data->north_path);
	free(g->data->west_path);
	free(g->data->south_path);
	free(g->data);
	free(g);
	exit(exit_code);
}
