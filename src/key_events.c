/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:40:48 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/11 15:09:21 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int	cub_keydown(int keycode, t_game *g)
{
	if (keycode == KEY_Q || keycode == KEY_ESC)
		handle_error(ERR_END, g, NULL, 1);
	else if (keycode == KEY_SPACE)
	{
		g->is_paused = !g->is_paused;
	}
	else if (!g->is_paused)
	{
		if (keycode == KEY_LEFT)
			g->pl.keys.left_pressed = 1;
		else if (keycode == KEY_RIGHT)
			g->pl.keys.right_pressed = 1;
		else if (keycode == KEY_W)
			g->pl.keys.w_pressed = 1;
		else if (keycode == KEY_A)
			g->pl.keys.a_pressed = 1;
		else if (keycode == KEY_S)
			g->pl.keys.s_pressed = 1;
		else if (keycode == KEY_D)
			g->pl.keys.d_pressed = 1;
		else if (keycode == KEY_E)
			action_door(g);
	}
	return (0);
}

int	cub_keyup(int k, t_game *g)
{
	if (k == KEY_LEFT)
		g->pl.keys.left_pressed = 0;
	else if (k == KEY_RIGHT)
		g->pl.keys.right_pressed = 0;
	else if (k == KEY_W)
		g->pl.keys.w_pressed = 0;
	else if (k == KEY_A)
		g->pl.keys.a_pressed = 0;
	else if (k == KEY_S)
		g->pl.keys.s_pressed = 0;
	else if (k == KEY_D)
		g->pl.keys.d_pressed = 0;
	return (0);
}
