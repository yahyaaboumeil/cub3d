/* file: raycasting.c */
#include "cub3d.h"

t_intersection	*ray(t_game *g, double rayAngle)
{
	t_intersection	*v_inter;
	t_intersection	*h_inter;

	rayAngle = normalize(rayAngle);
	v_inter = verticaldist(g, rayAngle);
	h_inter = horizontaldist(g, rayAngle);
	if (v_inter->distance < h_inter->distance)
	{
		v_inter->is_vert = true;
		free(h_inter);
		return (v_inter);
	}
	h_inter->is_vert = false;
	free(v_inter);
	return (h_inter);
}

static t_img	*get_texture(t_game *g, t_intersection *inter, double ray)
{
	if (inter->is_vert)
	{
		if (cos(ray) > 0)
			return (&g->tex_e);
		return (&g->tex_w);
	}
	if (sin(ray) > 0)
		return (&g->tex_s);
	return (&g->tex_n);
}

static void	draw_wall_strip(t_game *g, int i, double wall_h, t_intersection *in,
		double ray)
{
	t_img	*tex;
	int		texX;
	int		texY;
	int		y;
	double	step;
	double	texPos;
	double	top;
	double	wall_x;
	double	bottom;

	tex = get_texture(g, in, ray);
	if (in->is_vert)
		wall_x = g->py + (in->distance * sin(ray));
	else
		wall_x = g->px + (in->distance * cos(ray));
	wall_x -= floor(wall_x / TILE_SIZE) * TILE_SIZE;
	texX = (int)(wall_x * (double)tex->width / TILE_SIZE);
	if ((in->is_vert && cos(ray) > 0) || (!in->is_vert && sin(ray) < 0))
		texX = tex->width - texX - 1;
	top = (WIN_HEIGHT / 2.0) - (wall_h / 2.0);
	step = 1.0 * tex->height / wall_h;
	texPos = (top - WIN_HEIGHT / 2.0 + wall_h / 2.0) * step;
	y = (top < 0) ? 0 : top;
	bottom = (WIN_HEIGHT / 2.0) + (wall_h / 2.0);
	if (bottom >= WIN_HEIGHT)
		bottom = WIN_HEIGHT - 1;
	while (y < bottom)
	{
		texY = (int)texPos & (tex->height - 1);
		texPos += step;
		my_pixel_put(g, i, y, *(unsigned int *)(tex->addr + (texY
					* tex->line_len + texX * (tex->bpp / 8))));
		y++;
	}
}

typedef struct ray_casting
{
	double			ray_angle;
	double			wall_strip_height;
	double			dist_proj_plane;
	double			angle_step;
	int				i;
	t_intersection	*inter;
	double			dist;

}					t_ray_casting;

void	release_rays(t_game *game, t_intersection *inter_unused)
{
	t_ray_casting	help;

	(void)inter_unused;
	help.ray_angle = normalize(game->angle - (FOV / 2.0));
	help.dist_proj_plane = (WIN_WIDTH / 2.0) / tan(FOV / 2.0);
	help.angle_step = FOV / NUM_RAYS;
	help.i = 0;
	while (help.i < NUM_RAYS)
	{
		help.inter = ray(game, help.ray_angle);
		help.dist = cos(help.ray_angle - game->angle) * help.inter->distance;
		help.wall_strip_height = (TILE_SIZE / help.dist) * help.dist_proj_plane;
		draw_wall_strip(game, help.i, help.wall_strip_height, help.inter,
			help.ray_angle);
		free(help.inter);
		help.ray_angle = normalize(help.ray_angle + help.angle_step);
		help.i++;
	}
}
