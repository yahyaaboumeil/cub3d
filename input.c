/* file: input.c */
#include "cub3d.h"

typedef struct s_moves
{
	double	move_speed;
	double	rot_speed;
	double	new_px;
	double	new_py;
	double	move_angle;

}			t_moves;

static void	norm(t_game *g, int key, t_moves *help)
{
	if (key == 115 || key == XK_Down)
		help->move_angle += PI;
	if (key == 97)
		help->move_angle -= M_PI_2;
	if (key == 100)
		help->move_angle += M_PI_2;
	help->new_px = g->px + cos(help->move_angle) * help->move_speed;
	help->new_py = g->py + sin(help->move_angle) * help->move_speed;
	if (!is_wall(g, help->new_px, g->py))
		g->px = help->new_px;
	if (!is_wall(g, g->px, help->new_py))
		g->py = help->new_py;
}

int	handle_input(int key, t_game *g)
{
	t_moves	help;

	(1) && (help.rot_speed = 0.1, help.move_angle = g->angle,
		help.move_speed = 5.0);
	if (key == 65307)
		clean_all(g, 0);
	if (key == XK_Left)
		g->angle = normalize(g->angle - help.rot_speed);
	if (key == XK_Right)
		g->angle = normalize(g->angle + help.rot_speed);
	if (key == 119 || key == XK_Up || key == 115 || key == XK_Down || key == 97
		|| key == 100)
	{
		norm(g, key, &help);
	}
	render(g);
	return (0);
}
