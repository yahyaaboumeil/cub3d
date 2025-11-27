#ifndef CUB3D_H
#define CUB3D_H

#include "../minilibx-linux/mlx.h"
#include "../parsing/parsing.h"

typedef struct s_player {
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    double move_speed;
    double rot_speed;
} t_player;


typedef struct s_img 
{
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
} t_img;

typedef struct s_texture
{
    void *img;
    int width;
    int height;
} t_texture;

typedef struct s_info
{
    void *mlx;
    void *win;
    t_data     *data;
    t_texture north;
    t_texture south;
    t_texture east;
    t_texture west;
    t_img *frame;
    t_player    player;
    int         map_width;
    int         map_height;
} t_info;

void play(t_data *data);
#endif