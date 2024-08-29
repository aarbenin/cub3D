/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 07:35:56 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/29 08:03:33 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * Frees the memory allocated for a linked list of animations and their associated images.
 * 
 * @param g A pointer to the game structure, used to access the MiniLibX context.
 * @param start A pointer to the head of the linked list of animations.
 */
void	free_animation(t_game *g, t_list *start)
{
	t_list	*temp;

	temp = NULL;
	while (start)
	{
		temp = start;
		start = start->next;
		if (g && ((t_img *)temp->content)->i)
			mlx_destroy_image(g->mlx_ptr, ((t_img *)temp->content)->i);
		free(temp->content);
		free(temp);
	}
}

/**
 * Destroys all images and other graphical resources associated with the game.
 * 
 * @param g A pointer to the game structure, used to access the MiniLibX context and graphical resources.
 */

void	destroy_images(t_game *g)
{
	free_animation(g, g->tex.n_bak);
	free_animation(g, g->tex.s_bak);
	free_animation(g, g->tex.e_bak);
	free_animation(g, g->tex.w_bak);
	if (g->tex.b && g->tex.b->i)
		mlx_destroy_image(g->mlx_ptr, g->tex.b->i);
	if (g->win_img.i)
		mlx_destroy_image(g->mlx_ptr, g->win_img.i);
	if (g->scope && g->scope->i)
		mlx_destroy_image(g->mlx_ptr, g->scope->i);
	if (g->win_g.i)
		mlx_destroy_image(g->mlx_ptr, g->win_g.i);
	if (g->win_r.i)
		mlx_destroy_image(g->mlx_ptr, g->win_r.i);
	if (g->win_ptr)
		mlx_destroy_window(g->mlx_ptr, g->win_ptr);
	if (g->minimap.i)
		mlx_destroy_image(g->mlx_ptr, g->minimap.i);
	if (g->miniview.i)
		mlx_destroy_image(g->mlx_ptr, g->miniview.i);
	free(g->tex.b);
	free(g->scope);
}

/**
 * Cleans up all game resources and closes the game.
 * 
 * @param g A pointer to the game structure, used to access and free various resources.
 */
void	cleanup_game(t_game *g)
{
	if (!g)
		return ;
	ft_free_matrix(&g->map);
	if (g->fd > 0)
		close(g->fd);
	destroy_images(g);
	mlx_destroy_display(g->mlx_ptr);
	free(g->mlx_ptr);
}
