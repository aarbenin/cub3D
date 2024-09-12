/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:39:03 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 13:26:52 by aarbenin         ###   ########.fr       */
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
	// printf("New position: x = %f, y = %f\n", g->pl.position_x,
	// 	g->pl.position_y);
}
