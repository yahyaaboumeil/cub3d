#include "cub3d.h"

double distancebetwen2points(int x1, int y1, int x2, int y2)
{
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

int is_ray_facing_down(double ray_angle)
{
    return (ray_angle > 0 && ray_angle < PI);
}

int is_ray_facing_up(double ray_angle)
{
    return (!is_ray_facing_down(ray_angle));
}

int is_ray_facing_right(double ray_angle)
{
    return (ray_angle < PI * 0.5 || ray_angle > PI * 1.5);
}

int is_ray_facing_left(double ray_angle)
{
    return (!is_ray_facing_right(ray_angle));
}
