/* file: render.c */
#include "cub3d.h"

void my_pixel_put(t_game *g, int x, int y, int color)
{
    char *dst;

    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return ;
    dst = g->addr + (y * g->line_length + x * (g->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_map(t_game *g)
{
    int i;
    int j;

    i = 0;
    while (i < WIN_HEIGHT)
    {
        j = 0;
        while (j < WIN_WIDTH)
        {
            if (i < WIN_HEIGHT / 2)
                my_pixel_put(g, j, i, g->ceil_color);
            else
                my_pixel_put(g, j, i, g->floor_color);
            j++;
        }
        i++;
    }
}

void render(t_game *g)
{
    draw_map(g);
    release_rays(g, NULL);
    mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}
