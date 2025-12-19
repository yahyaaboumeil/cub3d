/* file: utils.c */
#include "cub3d.h"

unsigned int rgb_to_hex(int *rgb)
{
    return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

double normalize(double angle)
{
    angle = fmod(angle, (2 * PI));
    if (angle < 0)
        angle = angle + (2 * PI);
    return (angle);
}

double distancebetwen2points(int x1, int y1, int x2, int y2)
{
    return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}
