/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:37:32 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/17 09:29:22 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * Initializes the pointers to various sprite images and loads
 * texture images.
 *
 * Sets all sprite pointers to NULL initially to avoid accessing
 * uninitialized pointers.
 * Loads images for different textures and ensures they are
 * successfully loaded, reporting
 * an error if any texture fails to load.
 *
 * @param g Pointer to the game structure where sprite and
 * texture information is stored.
 */
void	init_sprites(t_game *g)
{
	g->win_img.i = NULL;
	g->minimap.i = NULL;
	g->tex.n = NULL;
	g->tex.n_bak = NULL;
	g->tex.s = NULL;
	g->tex.s_bak = NULL;
	g->tex.e = NULL;
	g->tex.e_bak = NULL;
	g->tex.w = NULL;
	g->tex.w_bak = NULL;
	g->scope = load_img(g->mlx_ptr, "textures/banana.xpm");
	if (!g->scope || !g->scope->i)
		handle_error(ERR_INV_PATH, g, NULL, 1);
}
