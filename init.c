/* file: init.c */
#include "cub3d.h"

static void load_texture(t_game *g, t_img *tex, char *path)
{
    tex->img = mlx_xpm_file_to_image(g->mlx, path, &tex->width, &tex->height);
    if (!tex->img)
    {
        printf("Error\nFailed to load texture: %s\n", path);
        exit(1);
    }
    tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, 
            &tex->line_len, &tex->endian);
}

void load_textures(t_game *g, t_data *data)
{
    load_texture(g, &g->tex_n, data->north_path);
    load_texture(g, &g->tex_s, data->south_path);
    load_texture(g, &g->tex_e, data->east_path);
    load_texture(g, &g->tex_w, data->west_path);
}

void init_player(t_game *g)
{
    int i;
    int j;

    i = 0;
    while (g->map[i])
    {
        j = 0;
        while (g->map[i][j])
        {
            if (strchr("NSWE", g->map[i][j]))
            {
                g->px = j * TILE_SIZE + (TILE_SIZE / 2);
                g->py = i * TILE_SIZE + (TILE_SIZE / 2);
                if (g->map[i][j] == 'N') g->angle = 3 * PI / 2;
                else if (g->map[i][j] == 'S') g->angle = PI / 2;
                else if (g->map[i][j] == 'E') g->angle = 0;
                else if (g->map[i][j] == 'W') g->angle = PI;
                g->map[i][j] = '0';
                return ;
            }
            j++;
        }
        i++;
    }
}
