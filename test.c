#include <unistd.h>
#include "minilibx-linux/mlx.h"
#include <stdio.h>

int main(void)
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 200, 200, "test");

    int w, h;
    void *img = mlx_xpm_file_to_image(mlx, "/home/yahya/cub3d/textures/north.xpm", &w, &h);
    if (!img)
        printf("Failed to load XPM!\n");
    else
        printf("Loaded XPM: %d x %d\n", w, h);

    mlx_loop(mlx);
}

