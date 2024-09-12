/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:39:03 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 09:34:06 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Moves the player left or right based on the input direction.
 * 
 * This function updates the player's new position by adding a displacement
 * vector scaled by the move speed and direction (left or right) using the
 * player's plane coordinates.
 * 
 * @param pl Pointer to the player structure.
 * @param move_speed Speed at which the player moves.
 * @param direction Direction of movement (1 for right, -1 for left).
 * @param move_data Pointer to the move data structure to update
 * the new position.
 */
static void	move_left_right(t_player *pl, double move_speed, int direction,
		t_move_data *move_data)
{
	move_data->new_x += direction * pl->plane_x * move_speed;
	move_data->new_y += direction * pl->plane_y * move_speed;
}

/**
 * @brief Moves the player forward or backward based on the input direction.
 * 
 * This function updates the player's new position by adding a
 * displacement
 * vector scaled by the move speed and direction (forward or backward)
 * using the
 * player's direction coordinates.
 * 
 * @param pl Pointer to the player structure.
 * @param move_speed Speed at which the player moves.
 * @param direction Direction of movement (1 for forward, -1 for
 * backward).
 * @param move_data Pointer to the move data structure to update
 * the new position.
 */
static void	move_forward_backward(t_player *pl, double move_speed,
		int direction, t_move_data *move_data)
{
	move_data->new_x += direction * pl->dir_x * move_speed;
	move_data->new_y += direction * pl->dir_y * move_speed;
}

/**
 * @brief Moves the player based on the pressed keys and updates the position.
 * 
 * This function calculates the new player position based on the movement
 * keys
 * pressed (W, A, S, D) and checks if the new position is valid (not
 * colliding 
 * with walls or doors). It updates the player's position accordingly.
 * 
 * @param g Pointer to the game structure.
 */
void	move_player(t_game *g)
{
	double		move_speed;
	t_move_data	move_data;

	move_speed = g->pl.speed;
	move_data.new_x = g->pl.position_x;
	move_data.new_y = g->pl.position_y;
	if (g->pl.keys.a_pressed)
		move_left_right(&g->pl, move_speed, -1, &move_data);
	if (g->pl.keys.d_pressed)
		move_left_right(&g->pl, move_speed, 1, &move_data);
	if (g->pl.keys.w_pressed)
		move_forward_backward(&g->pl, move_speed, 1, &move_data);
	if (g->pl.keys.s_pressed)
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

/**
 * @brief Rotates the player to the left by updating direction
 * and plane vectors.
 * 
 * This function rotates the player's view direction and plane coordinates
 * counterclockwise by a specified rotation speed.
 * 
 * @param pl Pointer to the player structure.
 * @param rotation_speed The speed at which the player rotates.
 */
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

/**
 * @brief Rotates the player based on the pressed keys for left
 * and right rotation.
 * 
 * This function checks if the left or right rotation keys are pressed and
 * updates the player's direction and plane coordinates accordingly.
 * 
 * @param g Pointer to the game structure.
 */
void	rotate_player(t_game *g)
{
	double	rotation_speed;

	rotation_speed = 0.01;
	if (g->pl.keys.left_pressed)
		rotate_left(&g->pl, rotation_speed);
	if (g->pl.keys.right_pressed)
		rotate_right(&g->pl, rotation_speed);
}
//_____________________mouse_move.c__________________________

/**
 * @brief Handles mouse movement to rotate the player view.
 * 
 * This function adjusts the player's rotation based on the mouse movement
 * relative to the center of the screen. It re-centers the mouse cursor after
 * each movement.
 * 
 * @param x The current x-coordinate of the mouse.
 * @param y The current y-coordinate of the mouse (not used).
 * @param g Pointer to the game structure.
 * @return 0 on success.
 */
int	mouse_move(int x, int y, t_game *g)
{
	int		center_x;
	double	rotation_speed_factor;

	if (g->is_paused)
		return (0);
	(void)y;
	center_x = WIN_W / 2;
	rotation_speed_factor = 0.005;
	if (abs(center_x - x) > 1)
	{
		if (x < center_x)
			rotate_left(&g->pl, (center_x - x) * rotation_speed_factor);
		else if (x > center_x)
			rotate_right(&g->pl, (x - center_x) * rotation_speed_factor);
		mlx_mouse_move(g->mlx_ptr, g->win_ptr, center_x, WIN_H / 2);
	}
	return (0);
}
