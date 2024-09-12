/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:07:32 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 13:20:36 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Sets up game attributes, raycasting, and hooks for handling input
 * events.
 *
 * @param g Pointer to the game structure.
 */
void	setup_game(t_game *g)
{
	init_attr(g);
	init_ray(g);
	mlx_hook(g->win_ptr, 02, 1L << 0, cub_keydown, g);
	mlx_hook(g->win_ptr, 03, 1L << 1, cub_keyup, g);
	mlx_hook(g->win_ptr, 17, 0, cub_exit, g);
	mlx_hook(g->win_ptr, 6, 1L << 6, mouse_input, g);
	mlx_mouse_move(g->mlx_ptr, g->win_ptr, WIN_W / 2, WIN_H / 2);
	mlx_loop_hook(g->mlx_ptr, update_cub, g);
	mlx_loop(g->mlx_ptr);
}
