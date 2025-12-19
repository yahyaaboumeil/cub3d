#include "cub3d.h"

void	clean_all(t_game *g, int exit_code)
{
	free_memory(g->map);
	mlx_destroy_window(g->mlx, g->win);
    if (!g->tex_s.img)
        mlx_destroy_image(g->mlx, g->tex_s.img);
    if (!g->tex_n.img)
        mlx_destroy_image(g->mlx, g->tex_n.img);
    if (!g->tex_w.img)
        mlx_destroy_image(g->mlx, g->tex_w.img);
    if (!g->tex_e.img)
        mlx_destroy_image(g->mlx, g->tex_e.img);
    mlx_destroy_image(g->mlx, g->img);
	mlx_destroy_display(g->mlx);
    free(g->mlx);
    free(g);
    exit(exit_code);
}