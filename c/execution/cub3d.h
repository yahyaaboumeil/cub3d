#ifndef CUB3D_H
#define CUB3D_H

#include "../minilibx-linux/mlx.h"
#include "../parsing/parsing.h"

#include "string.h"
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define WALL_XPM "sprites/wall.xpm"
#define FLOOR_XPM "sprites/floor.xpm"
#define COLL_XPM "sprites/coin-bag.xpm"
#define FRONT_XPM "sprites/player/front.xpm"
#define LEFT_XPM "sprites/player/left.xpm"
#define RIGHT_XPM "sprites/player/right.xpm"
#define BACK_XPM "sprites/player/back.xpm"
#define OPEN_EXIT_XPM "sprites/open-exit.xpm"
#define EXIT_XPM "sprites/exit-closed.xpm"

#include <math.h>

#define PI 3.14159265359
#define TILE_SIZE 32
#define WIN_WIDTH 1920
#define WIN_HEIGHT 1080
#define MAX_RAY_LENGTH 200

#define MINIMAP_SCALE 8  // Each tile will be 8x8 pixels 
#define MINIMAP_X 20     // X position of minimap
#define MINIMAP_Y 20     // Y position of minimap

#define NUM_RAYS WIN_WIDTH
#define FOV (M_PI / 3) // 60 degrees

typedef struct s_intersection
{
	bool is_vert;
	int x;
	int y;
	double distance;

} t_intersection;

typedef struct s_game
{
	t_data *data;
	void    *mlx;
	void    *win;
	void    *img;
	char    *addr;
	int     bits_per_pixel;
	int     line_length;
	int     endian;

	int px, py;         // player pixel coordinates
	double angle;       // player direction
	int x, y;           // player tile coordinates

			char **map;
} t_game;

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

double distancebetwen2points(int x1, int y1, int x2, int y2);
int is_ray_facing_down(double ray_angle);
int is_ray_facing_up(double ray_angle);
int is_ray_facing_right(double ray_angle);
int is_ray_facing_left(double ray_angle);

t_intersection *horizontaldist(t_game *g, double ray_angle);
t_intersection *verticaldist(t_game *g, double ray_angle);

void draw_map(t_game *g);
int     calcul_rgb(int color[3]);
void my_pixel_put(t_game *g, int x, int y, int color);
double normalize(double angle);
bool istherewall(t_game *g, double x, double y);
void release_rays(t_game *game, t_intersection *inter);
void    cub3d(t_data *data);


void play(t_data *data);
#endif
