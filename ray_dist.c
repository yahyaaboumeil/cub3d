/* file: ray_dist.c */
#include "cub3d.h"

static void init_vars_v(t_game *g, double angle, double *step, double *intercept)
{
    intercept[0] = floor(g->px / TILE_SIZE) * TILE_SIZE;
    if (is_ray_facing_right(angle))
        intercept[0] += TILE_SIZE;
    intercept[1] = g->py + (intercept[0] - g->px) * tan(angle);
    step[0] = TILE_SIZE;
    if (is_ray_facing_left(angle))
        step[0] = -TILE_SIZE;
    step[1] = TILE_SIZE * tan(angle);
    if (is_ray_facing_up(angle) && step[1] > 0)
        step[1] = -step[1];
    if (is_ray_facing_down(angle) && step[1] < 0)
        step[1] = -step[1];
}

t_intersection *verticaldist(t_game *g, double ray_angle)
{
    double          intercept[2]; // 0=x, 1=y
    double          step[2];      // 0=x, 1=y
    t_intersection  *inter;

    inter = malloc(sizeof(t_intersection));
    init_vars_v(g, ray_angle, step, intercept);
    if (is_ray_facing_left(ray_angle))
        intercept[0] -= 0.0001;
    while (!istherewall(g, intercept[0], intercept[1]))
    {
        intercept[0] += step[0];
        intercept[1] += step[1];
    }
    inter->x = intercept[0];
    inter->y = intercept[1];
    inter->distance = distancebetwen2points(g->px, g->py, 
            intercept[0], intercept[1]);
    return (inter);
}

static void init_vars_h(t_game *g, double angle, double *step, double *intercept)
{
    intercept[1] = floor(g->py / TILE_SIZE) * TILE_SIZE;
    if (is_ray_facing_down(angle))
        intercept[1] += TILE_SIZE;
    intercept[0] = g->px + (intercept[1] - g->py) / tan(angle);
    step[1] = TILE_SIZE;
    if (is_ray_facing_up(angle))
        step[1] *= -1;
    step[0] = TILE_SIZE / tan(angle);
    if (is_ray_facing_left(angle) && step[0] > 0)
        step[0] = -step[0];
    if (is_ray_facing_right(angle) && step[0] < 0)
        step[0] = -step[0];
}

t_intersection *horizontaldist(t_game *g, double ray_angle)
{
    double          intercept[2];
    double          step[2];
    t_intersection  *inter;

    inter = malloc(sizeof(t_intersection));
    init_vars_h(g, ray_angle, step, intercept);
    if (is_ray_facing_up(ray_angle))
        intercept[1] -= 0.0001;
    while (!istherewall(g, intercept[0], intercept[1]))
    {
        intercept[0] += step[0];
        intercept[1] += step[1];
    }
    inter->x = intercept[0];
    inter->y = intercept[1];
    inter->distance = distancebetwen2points(g->px, g->py, 
            intercept[0], intercept[1]);
    return (inter);
}
