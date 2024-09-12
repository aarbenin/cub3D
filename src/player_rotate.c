/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:25:45 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 11:34:01 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	rotate_left(t_player *pl, double rotation_speed)
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
void	rotate_right(t_player *pl, double rotation_speed)
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
