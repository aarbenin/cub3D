#include "../inc/cub3D.h"

static void	move_left_right(t_player *pl, double move_speed, int direction,
		t_move_data *move_data)
{
	move_data->new_x += direction * pl->plane_x * move_speed;
	move_data->new_y += direction * pl->plane_y * move_speed;
}

static void	move_forward_backward(t_player *pl, double move_speed,
		int direction, t_move_data *move_data)
{
	move_data->new_x += direction * pl->dir_x * move_speed;
	move_data->new_y += direction * pl->dir_y * move_speed;
}

void	move_player(t_game *g)
{
	double		move_speed;
	t_move_data	move_data;

	move_speed = g->pl.speed;
	move_data.new_x = g->pl.position_x;
	move_data.new_y = g->pl.position_y;
	if (g->pl.keys.a_pressed) // Move left
		move_left_right(&g->pl, move_speed, -1, &move_data);
	if (g->pl.keys.d_pressed) // Move right
		move_left_right(&g->pl, move_speed, 1, &move_data);
	if (g->pl.keys.w_pressed) // Move forward
		move_forward_backward(&g->pl, move_speed, 1, &move_data);
	if (g->pl.keys.s_pressed) // Move backward
		move_forward_backward(&g->pl, move_speed, -1, &move_data);
	if (g->map[(int)move_data.new_y][(int)move_data.new_x] != '1'
		&& g->map[(int)move_data.new_y][(int)move_data.new_x] != 'D')
	{
		g->pl.position_x = move_data.new_x;
		g->pl.position_y = move_data.new_y;
	}
	printf("New position: x = %f, y = %f\n", g->pl.position_x,
		g->pl.position_y);
}

static void	rotate_left(t_player *pl, double rotation_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = pl->dir_x;
	pl->dir_x = pl->dir_x * cos(-rotation_speed) - pl->dir_y
		* sin(-rotation_speed);
	pl->dir_y = old_dir_x * sin(-rotation_speed) + pl->dir_y
		* cos(-rotation_speed);
	old_plane_x = pl->plane_x;
	pl->plane_x = pl->plane_x * cos(-rotation_speed) - pl->plane_y
		* sin(-rotation_speed);
	pl->plane_y = old_plane_x * sin(-rotation_speed) + pl->plane_y
		* cos(-rotation_speed);
}

static void	rotate_right(t_player *pl, double rotation_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = pl->dir_x;
	pl->dir_x = pl->dir_x * cos(rotation_speed) - pl->dir_y
		* sin(rotation_speed);
	pl->dir_y = old_dir_x * sin(rotation_speed) + pl->dir_y
		* cos(rotation_speed);
	old_plane_x = pl->plane_x;
	pl->plane_x = pl->plane_x * cos(rotation_speed) - pl->plane_y
		* sin(rotation_speed);
	pl->plane_y = old_plane_x * sin(rotation_speed) + pl->plane_y
		* cos(rotation_speed);
}

void	rotate_player(t_game *g)
{
	double	rotation_speed;

	rotation_speed = 0.01;
	if (g->pl.keys.left_pressed)
		rotate_left(&g->pl, rotation_speed);
	if (g->pl.keys.right_pressed)
		rotate_right(&g->pl, rotation_speed);
	// printf("Rotated Direction: dir_x = %f, dir_y = %f\n",
	// 	g->pl.dir_x, g->pl.dir_y);
	// printf("Rotated Plane: plane_x = %f, plane_y = %f\n",
	// 	g->pl.plane_x, g->pl.plane_y);
}
//_____________________mouse_move.c__________________________

int	mouse_move(int x, int y, t_game *g)
{
	int		center_x;
	double	rotation_speed_factor;

	(void)y;
	center_x = WIN_W / 2;
	rotation_speed_factor = 0.005;
	// проверяем, насколько сильно отклонился от центра курсор прежде, чем произойдет вызов функции
	if (abs(center_x - x) > 1) // пока установила значение в 1 пиксель, нужно будет подобрать оптимальное.
	{
		if (x < center_x)
			rotate_left(&g->pl, (center_x - x) * rotation_speed_factor);
		else if (x > center_x)
			rotate_right(&g->pl, (x - center_x) * rotation_speed_factor);
		// Сбрасываем курсор в центр окна
		mlx_mouse_move(g->mlx_ptr, g->win_ptr, center_x, WIN_H / 2);
	}
	return (0);
}
