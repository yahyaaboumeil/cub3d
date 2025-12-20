#include "cub3d.h"

int	is_wall(t_game *g, int px, int py)
{
	int	tile_x;
	int	tile_y;

	tile_x = px / TILE_SIZE;
	tile_y = py / TILE_SIZE;
	if (tile_y < 0 || tile_y >= g->map_rows)
		return (1);
	if (!g->map[tile_y] || tile_x < 0
		|| tile_x >= (int)ft_strlen(g->map[tile_y]))
		return (1);
	return (g->map[tile_y][tile_x] == '1');
}

int	istherewall(t_game *g, double x, double y)
{
	int	xx;
	int	yy;

	xx = x / TILE_SIZE;
	yy = y / TILE_SIZE;
	if (yy < 0 || yy >= g->map_rows)
		return (1);
	if (!g->map[yy] || xx < 0 || xx >= (int)ft_strlen(g->map[yy]))
		return (1);
	return (g->map[yy][xx] == '1');
}
