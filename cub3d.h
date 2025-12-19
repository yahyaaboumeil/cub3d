/* file: cub3d.h */
#ifndef CUB3D_H
# define CUB3D_H

# include "parsing/parsing.h"
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>

// Macros
# define PI 3.14159265359
# define TILE_SIZE 32
# define WIN_WIDTH 1920 
# define WIN_HEIGHT 1080 
# define NUM_RAYS WIN_WIDTH
# define FOV 1.0471975512 // (M_PI / 3)

# ifndef M_PI_2
#  define M_PI_2 1.57079632679
# endif

typedef struct s_intersection
{
    bool    is_vert;
    int     x;
    int     y;
    double  distance;
} t_intersection;

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;
    int     height;
} t_img;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    
    // Textures
    t_img   tex_n;
    t_img   tex_s;
    t_img   tex_e;
    t_img   tex_w;

    // Colors
    int     floor_color;
    int     ceil_color;

    // Player
    int     px;
    int     py;
    double  angle;
    
    // Map
    int     map_rows;
    char    **map;
} t_game;

/* main.c */
int             main(int argc, char **argv);

/* init.c */
void            load_textures(t_game *g, t_data *data);
void            init_player(t_game *g);

/* input.c */
int             handle_input(int key, t_game *g);

/* render.c */
void            my_pixel_put(t_game *g, int x, int y, int color);
void            draw_map(t_game *g);
void            render(t_game *g);

/* map_check.c */
int             is_wall(t_game *g, int px, int py);
int             istherewall(t_game *g, double x, double y);

/* utils.c */
unsigned int    rgb_to_hex(int *rgb);
double          normalize(double angle);
double          distancebetwen2points(int x1, int y1, int x2, int y2);

/* ray_dir.c */
int             is_ray_facing_down(double ray_angle);
int             is_ray_facing_up(double ray_angle);
int             is_ray_facing_right(double ray_angle);
int             is_ray_facing_left(double ray_angle);

/* ray_dist.c */
t_intersection  *verticaldist(t_game *g, double ray_angle);
t_intersection  *horizontaldist(t_game *g, double ray_angle);

/* raycasting.c */
t_intersection  *ray(t_game *g, double rayAngle);
void            release_rays(t_game *game, t_intersection *inter_unused);

#endif
