#include "cub3d.h"

void load_texture(void *mlx, t_texture *t, char *path)
{
    t->img = mlx_xpm_file_to_image(mlx, path, &t->width, &t->height);
    if (!t->img)
    {
        printf("Error\nTexture failed: %s\n", path);
        exit(1);
    }
}

void load_all_textures(t_info *d)
{
    load_texture(d->mlx, &d->north, d->data->north_path);
    load_texture(d->mlx, &d->south, d->data->south_path);
    load_texture(d->mlx, &d->east, d->data->east_path);
    load_texture(d->mlx, &d->west, d->data->west_path);
}

static void init(t_info **info)
{
    (*info)->north.height = 0;
    (*info)->north.width = 0;
    (*info)->west.height = 0;
    (*info)->north.width = 0;
    (*info)->south.width = 0;
    (*info)->south.height = 0;
    (*info)->east.height = 0;
    (*info)->east.width = 0;
    (*info)->frame = malloc(sizeof(t_img));
    (*info)->frame->endian = 0;
    (*info)->frame->line_len = 0;
    
}

void free_stuct(t_data *d)
{
    free_memory(d->map);
    free(d->east_path);
    free(d->north_path);
    free(d->south_path);
    free(d->west_path);
    
    free(d);
}

void play(t_data *dat)
{
    t_info *d;
    d = malloc(sizeof(t_info));
    init(&d);
    d->data = dat;
    d->mlx = mlx_init();
    d->win = mlx_new_window(d->mlx, 800, 600, "cub3D");

    // load_all_textures(d);
    // d->frame->img = mlx_new_image(d->mlx, 800, 600);
    // d->frame->addr = mlx_get_data_addr(d->frame->img, &d->frame->bpp,
    //                                   &d->frame->line_len, &d->frame->endian);

    // init_player(d);

    // mlx_hook(d->win, 2, 1L << 0, handle_key, d); // key press
    // mlx_loop_hook(d->mlx, render_frame, d);      // main loop
    // mlx_loop(d->mlx);
    
    // free(d);
    free_stuct(dat);
    // mlx_destroy_display(d->mlx);
    // mlx_destroy_window(d->mlx, d->win);
    free(d->frame);
    free(d);
}

