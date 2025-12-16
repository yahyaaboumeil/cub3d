/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 10:04:13 by yaboumei          #+#    #+#             */
/*   Updated: 2025/12/15 11:28:37 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	normalize(double angle)
{
	angle = fmod(angle , (2 * PI));
	if (angle < 0)
		angle = angle + (2 * PI);
	return angle;
}

void my_pixel_put(t_game *g, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return;
	dst = g->addr + (y * g->line_length + x * (g->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	calcul_rgb(int color[3])
{
	return ((color[0] << 16) + (color[1] << 8) + (color[2]));
}

void draw_map(t_game *g)
{
	int	i;
	int	j;

	i = 0;	
	j = 0;
	while ( i < WIN_HEIGHT)
	{
		while (j < WIN_WIDTH)
		{
			if (i < WIN_HEIGHT / 2)
				my_pixel_put(g, j,i , calcul_rgb(g->data->c_color)); 
			else
				my_pixel_put(g, j,i , calcul_rgb(g->data->f_color)); 
			j++;
		}
		j = 0;
		i++;
	}
}

bool istherewall(t_game *g, double x, double y)
{
	int	xx;
	int	yy;

	yy = y / TILE_SIZE;
	xx = x / TILE_SIZE;
	if (xx < 0 || yy < 0)
		return 1;
	if (yy >= g->data->hight || xx >= g->data->width) 
		return 1;
	return (g->map[yy][xx] == '1'); // FIXED
}

