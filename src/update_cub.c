/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:33:07 by ogoman            #+#    #+#             */
/*   Updated: 2024/09/12 13:20:36 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Updates animations and timers based on the current frame.
 * 
 * This function checks if it's time to update animations by comparing the
 * current frame count with the rate at which animations should be updated.
 * 
 * @param g Pointer to the game structure.
 */
static void	update_animations_and_timer(t_game *g)
{
	if (!(g->nframes % (6 * g->rate)))
		update_anim(g);
}

/**
 * @brief Updates the game screen by redrawing all necessary elements.
 * 
 * This function clears the screen, draws the background, casts
 * rays for rendering,
 * redraws the scope, and updates the minimap.
 * 
 * @param g Pointer to the game structure.
 */
static void	update_screen(t_game *g)
{
	clear_image(&g->win_img, 0x000000);
	draw_background(g);
	cast_rays(g);
	redraw_elem(g, *g->scope, WIN_W / 2 - g->scope->width / 2, WIN_H / 2
		- g->scope->height / 2);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->win_img.i, 0, 0);
	draw_minimap(g);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->minimap.i, 10, 10);
}

/**
 * @brief Checks the pause state and handles the display of the pause screen.
 * 
 * This function determines if the game is in a paused state and, if so,
 * displays the pause screen. It also tracks the pause state to avoid
 * redundant operations.
 * 
 * @param g Pointer to the game structure.
 */
static void	check_pause_state(t_game *g)
{
	if (g->is_paused)
	{
		if (g->was_paused != 1)
		{
			printf("debug: Game is paused, displaying pause screen.\n");
			display_pause_screen(g);
			g->was_paused = 1;
		}
	}
	else
	{
		if (g->was_paused == 1)
			g->was_paused = 0;
	}
}

/**
 * @brief Updates the game state and handles frame updates.
 * 
 * This function is called every frame to handle game
 * updates, including checking
 * pause state, updating animations, processing player
 * input, and redrawing the screen.
 * 
 * @param param Pointer to the game structure.
 * @return Returns 0 to indicate successful execution.
 */

/**
 * Redraws an image element onto the game window at specified coordinates.
 *

 * @param g A pointer to a t_text_game structure that contains
 game state information.
 * @param img The image to be drawn.
 * @param x The x-coordinate where the image should be placed.
 * @param y The y-coordinate where the image should be placed.
 *
 * This function places the specified image onto the game window
 * at the given coordinates,
 * combining it with the existing window image. It uses a blending
 * color of 0xFF000000
 * to ensure proper overlay.
 */
void	redraw_elem(t_game *g, t_img img, int x, int y)
{
	int		p[2];
	t_img	images[2];

	p[0] = x;
	p[1] = y;
	images[0] = img;
	images[1] = g->win_img;
	mlx_img_to_img(p, images, 0xFF000000);
}

int	update_cub(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	check_pause_state(g);
	if (!(g->is_paused) && !(g->nframes % g->rate))
	{
		update_animations_and_timer(g);
		keyboard_input(g);
		update_screen(g);
	}
	g->frame_count++;
	return (0);
}
