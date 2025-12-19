/* file: input.c */
#include "cub3d.h"

int handle_input(int key, t_game *g)
{
    double  move_speed;
    double  rot_speed;
    double  new_px;
    double  new_py;
    double  move_angle;

    move_speed = 5.0;
    rot_speed = 0.1;
    move_angle = g->angle;
    if (key == 65307)
        exit(0);
    if (key == XK_Left)
        g->angle = normalize(g->angle - rot_speed);
    if (key == XK_Right)
        g->angle = normalize(g->angle + rot_speed);
    if (key == 119 || key == XK_Up || key == 115 || key == XK_Down 
        || key == 97 || key == 100)
    {
        if (key == 115 || key == XK_Down) move_angle += PI;
        if (key == 97) move_angle -= M_PI_2;
        if (key == 100) move_angle += M_PI_2;
        new_px = g->px + cos(move_angle) * move_speed;
        new_py = g->py + sin(move_angle) * move_speed;
        if (!is_wall(g, new_px, g->py)) g->px = new_px;
        if (!is_wall(g, g->px, new_py)) g->py = new_py;
    }
    render(g);
    return (0);
}
