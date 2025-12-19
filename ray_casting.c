/* file: raycasting.c */
#include "cub3d.h"

t_intersection *ray(t_game *g, double rayAngle)
{
    t_intersection *v_inter;
    t_intersection *h_inter;

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

static t_img *get_texture(t_game *g, t_intersection *inter, double ray)
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

static void draw_wall_strip(t_game *g, int i, double wall_h, t_intersection *in, double ray)
{
    t_img   *tex;
    int     texX;
    int     texY;
    int     y;
    double  step;
    double  texPos;
    double  top;
    
    tex = get_texture(g, in, ray);
    double wall_x;
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
    double bottom = (WIN_HEIGHT / 2.0) + (wall_h / 2.0);
    if (bottom >= WIN_HEIGHT) bottom = WIN_HEIGHT - 1;
    while (y < bottom)
    {
        texY = (int)texPos & (tex->height - 1);
        texPos += step;
        my_pixel_put(g, i, y, *(unsigned int*)(tex->addr + 
            (texY * tex->line_len + texX * (tex->bpp / 8))));
        y++;
    }
}

void release_rays(t_game *game, t_intersection *inter_unused)
{
    double  start_ray;
    double  wall_strip_height;
    double  dist_proj_plane;
    double  angle_step;
    int     i;

    (void)inter_unused;
    start_ray = normalize(game->angle - (FOV / 2.0));
    dist_proj_plane = (WIN_WIDTH / 2.0) / tan(FOV / 2.0);
    angle_step = FOV / NUM_RAYS;
    i = 0;
    while (i < NUM_RAYS)
    {
        t_intersection *inter = ray(game, start_ray);
        double dist = cos(start_ray - game->angle) * inter->distance;
        wall_strip_height = (TILE_SIZE / dist) * dist_proj_plane;
        draw_wall_strip(game, i, wall_strip_height, inter, start_ray);
        free(inter);
        start_ray = normalize(start_ray + angle_step);
        i++;
    }
}
