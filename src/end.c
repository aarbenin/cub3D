/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 07:35:56 by ogoman            #+#    #+#             */
/*   Updated: 2024/09/17 06:37:30 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * Frees the memory allocated for a linked list of animations and their
 * associated images.
 * 
 * @param g A pointer to the game structure, used to access the MiniLibX
 * context.
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
 * Destroys all images and other graphical resources associated with the
 * game.
 * 
 * @param g A pointer to the game structure, used to access the MiniLibX
 * context and graphical resources.
 */

// void	destroy_images(t_game *g)
// {
// 	free_animation(g, g->tex.n_bak);
// 	free_animation(g, g->tex.s_bak);
// 	free_animation(g, g->tex.e_bak);
// 	free_animation(g, g->tex.w_bak);
// 	if (g->tex.door_closed && g->tex.door_closed->i)
// 	{
// 		mlx_destroy_image(g->mlx_ptr, g->tex.door_closed->i);
// 		free(g->tex.door_closed);
// 	}
// 	if (g->tex.door_open && g->tex.door_open->i)
// 		mlx_destroy_image(g->mlx_ptr, g->tex.door_open->i);
// 	if (g->tex.b && g->tex.b->i)
// 		mlx_destroy_image(g->mlx_ptr, g->tex.b->i);
// 	if (g->win_img.i)
// 		mlx_destroy_image(g->mlx_ptr, g->win_img.i);
// 	if (g->scope && g->scope->i)
// 		mlx_destroy_image(g->mlx_ptr, g->scope->i);
// 	if (g->win_ptr)
// 		mlx_destroy_window(g->mlx_ptr, g->win_ptr);
// 	if (g->minimap.i)
// 		mlx_destroy_image(g->mlx_ptr, g->minimap.i);
// 	if (g->miniview.i)
// 		mlx_destroy_image(g->mlx_ptr, g->miniview.i);
// 	if (g->welcome_screen && g->welcome_screen->i)
// 	{
// 		mlx_destroy_image(g->mlx_ptr, g->welcome_screen->i);
// 		free(g->welcome_screen);
// 	}	
// 	if (g->scaled_welcome.i)
// 		mlx_destroy_image(g->mlx_ptr, g->scaled_welcome.i);
// 	free(g->tex.b);
// 	free(g->scope);
// }

/**
 * Cleans up all game resources and closes the game.
 * 
 * @param g A pointer to the game structure, used to access and free
 * various resources.
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

/**
 * Frees the memory associated with the loaded textures and 
 * destroys any images that were created for textures.
 *
 * The function ensures that all texture-related images are
 * safely freed and destroyed, including animations and specific
 * textures for doors and other game elements.
 *
 * @param g Pointer to the game structure that holds texture
 * information.
 */
void	destroy_textures(t_game *g)
{
	free_animation(g, g->tex.n_bak);
	free_animation(g, g->tex.s_bak);
	free_animation(g, g->tex.e_bak);
	free_animation(g, g->tex.w_bak);
	if (g->tex.door_closed && g->tex.door_closed->i)
	{
		mlx_destroy_image(g->mlx_ptr, g->tex.door_closed->i);
		free(g->tex.door_closed);
	}
	if (g->tex.door_open && g->tex.door_open->i)
		mlx_destroy_image(g->mlx_ptr, g->tex.door_open->i);
	if (g->tex.b && g->tex.b->i)
		mlx_destroy_image(g->mlx_ptr, g->tex.b->i);
	free(g->tex.b);
}

/**
 * Helper function that frees and destroys various images 
 * used in the game.
 *
 * This function handles the destruction of window images, 
 * scope, minimap, welcome screens, and any other game 
 * elements that have been allocated.
 *
 * @param g Pointer to the game structure that holds image 
 * information.
 */
void	destroy_images_helper(t_game *g)
{
	if (g->win_img.i)
		mlx_destroy_image(g->mlx_ptr, g->win_img.i);
	if (g->scope && g->scope->i)
	{
		mlx_destroy_image(g->mlx_ptr, g->scope->i);
		free(g->scope);
	}
	if (g->minimap.i)
		mlx_destroy_image(g->mlx_ptr, g->minimap.i);
	if (g->welcome_screen && g->welcome_screen->i)
	{
		mlx_destroy_image(g->mlx_ptr, g->welcome_screen->i);
		free(g->welcome_screen);
	}
	if (g->scaled_welcome.i)
		mlx_destroy_image(g->mlx_ptr, g->scaled_welcome.i);
}

/**
 * Destroys the game window if it exists and frees any 
 * associated memory.
 *
 * This function ensures that the window pointer is valid 
 * before calling the MLX function to destroy the window.
 *
 * @param g Pointer to the game structure that holds the 
 * window information.
 */
void	destroy_window(t_game *g)
{
	if (g->win_ptr)
		mlx_destroy_window(g->mlx_ptr, g->win_ptr);
}

/**
 * Main function to destroy all images, textures, and the 
 * game window.
 *
 * Calls helper functions to clean up textures, images, and 
 * the game window in a structured manner, ensuring that 
 * memory is properly freed and no leaks occur.
 *
 * @param g Pointer to the game structure that holds all 
 * resource pointers.
 */
void	destroy_images(t_game *g)
{
	destroy_textures(g);
	destroy_images_helper(g);
	destroy_window(g);
}
