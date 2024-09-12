/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:36:59 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 11:37:23 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

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
