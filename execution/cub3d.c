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
// void init_player(t_info *d)
// {
//     int x, y;

//     for (y = 0; y < d->map_height; y++)
//     {
//         for (x = 0; x < d->map_width; x++)
//         {
//             if (d->data->map[y][x] == 'N' || d->data->map[y][x] == 'S' ||
//                 d->data->map[y][x] == 'E' || d->data->map[y][x] == 'W')
//             {
//                 d->player.x = x + 0.5;
//                 d->player.y = y + 0.5;
//                 if (d->data->map[y][x] == 'N') { d->player.dir_x = 0; d->player.dir_y = -1; d->player.plane_x = 0.66; d->player.plane_y = 0; }
//                 if (d->data->map[y][x] == 'S') { d->player.dir_x = 0; d->player.dir_y = 1;  d->player.plane_x = -0.66; d->player.plane_y = 0; }
//                 if (d->data->map[y][x] == 'E') { d->player.dir_x = 1; d->player.dir_y = 0;  d->player.plane_x = 0; d->player.plane_y = 0.66; }
//                 if (d->data->map[y][x] == 'W') { d->player.dir_x = -1; d->player.dir_y = 0; d->player.plane_x = 0; d->player.plane_y = -0.66; }
//                 return;
//             }
//         }
//     }
// }
void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}
void draw_background(t_info *d)
{
    int x, y;

    // Ceiling
    for (y = 0; y < 600 / 2; y++)
        for (x = 0; x < 800; x++)
            put_pixel(d->frame, x, y, 0x87CEEB); // sky blue

    // Floor
    for (y = 600 / 2; y < 600; y++)
        for (x = 0; x < 800; x++)
            put_pixel(d->frame, x, y, 0x654321); // brown
}
int render_frame(t_info *d)
{
    draw_background(d);
    // TODO: draw walls using raycasting here later
    mlx_put_image_to_window(d->mlx, d->win, d->frame->img, 0, 0);
    return 0;
}
int handle_key(int key)
{
    if (key == 53) // ESC
        exit(0);
    // TODO: W, A, S, D movement
    // TODO: Left / Right rotation
    return 0;
}

void free_stuct(t_data *d)
{
    free_memory(d->map);
    // free(d->c_color);
    // free(d->f_color);
    free(d->east_path);
    free(d->north_path);
    free(d->south_path);
    free(d->west_path);
}
void play(t_data *dat)
{
    t_info *d;
    d = malloc(sizeof(t_info));
    init(&d);
    d->data = dat;
    d->mlx = mlx_init();
    d->win = mlx_new_window(d->mlx, 800, 600, "cub3D");

    load_all_textures(d);
    d->frame->img = mlx_new_image(d->mlx, 800, 600);
    d->frame->addr = mlx_get_data_addr(d->frame->img, &d->frame->bpp,
                                      &d->frame->line_len, &d->frame->endian);

    // init_player(d);

    mlx_hook(d->win, 2, 1L << 0, handle_key, d); // key press
    mlx_loop_hook(d->mlx, render_frame, d);      // main loop
    mlx_loop(d->mlx);
    
    free(d);
    free_stuct(dat);
    
}

// void play(t_data *data)
// {
//     t_info *info;

//     info = malloc(sizeof(t_info));
//     init(&info);
//     info->data = data;
//     info->mlx = mlx_init();
//     if (!info->mlx)
//         exit(1);
        
//     info->win = mlx_new_window(info->mlx, 800, 600, "cub3D");
//     if (!info->win)
//         exit(1);

//     load_all_textures(info);
    
//     info->frame->img = mlx_new_image(info->mlx, 800, 600);
//     if (!info->frame->img)
//         exit(1);

//     info->frame->addr = mlx_get_data_addr(info->frame->img,
//                                         &info->frame->bpp, &info->frame->line_len, &info->frame->endian);
//     info->frame->img = mlx_new_image(info->mlx, 800, 600);
//     if (!info->frame->img)
//         exit(1);

//     info->frame->addr = mlx_get_data_addr(info->frame->img,
//                                         &info->frame->bpp, &info->frame->line_len, &info->frame->endian);
//     mlx_loop(info->mlx);
// }
