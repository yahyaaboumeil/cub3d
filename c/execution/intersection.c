#include "cub3d.h"

t_intersection *verticaldist(t_game *g, double ray_angle)
{
        double x_intercept;
        double y_intercept;
        double x_step;
        double y_step;
        t_intersection *inter;

        inter = malloc(sizeof(t_intersection));
        x_intercept = floor(g->px / TILE_SIZE) * TILE_SIZE;
        if (is_ray_facing_right(ray_angle))
                x_intercept += TILE_SIZE;
        y_intercept = g->py + (x_intercept - g->px) * tan(ray_angle);
        x_step = TILE_SIZE;
        if (is_ray_facing_left(ray_angle))
                x_step = -TILE_SIZE;
        y_step = TILE_SIZE * tan(ray_angle);
        if (is_ray_facing_up(ray_angle) && y_step > 0)
                y_step = -y_step;
        if (is_ray_facing_down(ray_angle) && y_step < 0)
                y_step = -y_step;
        if (is_ray_facing_left(ray_angle))
                x_intercept -= 0.0001;
        while (!istherewall(g, x_intercept, y_intercept))
        {
                x_intercept += x_step;
                y_intercept += y_step;
        }
        inter->x = x_intercept;
        inter->y = y_intercept;
        inter->distance = distancebetwen2points(g->px, g->py, x_intercept, y_intercept);
        return inter;
}

t_intersection *horizontaldist(t_game *g, double ray_angle)
{
        double x_intercept;
        double y_intercept;
        double x_step;
        double y_step;
        t_intersection *inter;

        inter = malloc(sizeof(t_intersection));
        y_intercept= floor(g->py / TILE_SIZE) * TILE_SIZE;
        if (is_ray_facing_down(ray_angle))
                y_intercept += TILE_SIZE;
        x_intercept = g->px + (y_intercept - g->py) / tan(ray_angle);
        y_step = TILE_SIZE;
        if (is_ray_facing_up(ray_angle))
                y_step *= -1;
        x_step = TILE_SIZE / tan(ray_angle);
        if (is_ray_facing_left(ray_angle) && x_step > 0)
                x_step = -x_step;
        if (is_ray_facing_right(ray_angle) && x_step < 0)
                x_step = -x_step;
        if (is_ray_facing_up(ray_angle))
                y_intercept -= 0.0001;
        while (!istherewall(g, x_intercept, y_intercept))
        {
                x_intercept += x_step;
                y_intercept += y_step;
        }
        inter->x = x_intercept;
        inter->y = y_intercept;
        inter->distance = distancebetwen2points(g->px, g->py, x_intercept, y_intercept);
        return inter;
}




