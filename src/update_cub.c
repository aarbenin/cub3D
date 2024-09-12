/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:33:07 by ogoman            #+#    #+#             */
/*   Updated: 2024/09/12 07:52:19 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Clears the given image with a solid color.
 * 
 * This function sets every pixel in the image to the specified color.
 * 
 * @param img Pointer to the image structure to be cleared.
 * @param color Color value to fill the image with.
 */
void	clear_image(t_img *img, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

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
 * @brief Handles player input for movement and rotation.
 * 
 * This function checks if any movement or rotation keys are pressed and
 * updates the player's position and orientation accordingly.
 * 
 * @param g Pointer to the game structure.
 */
static void	handle_player_input(t_game *g)
{
	if (g->pl.keys.w_pressed || g->pl.keys.a_pressed
		|| g->pl.keys.s_pressed
		|| g->pl.keys.d_pressed
		|| g->pl.keys.left_pressed
		|| g->pl.keys.right_pressed)
	{
		move_player(g);
		rotate_player(g);
	}
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
int	cub_update(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	check_pause_state(g);
	if (!(g->is_paused) && !(g->nframes % g->rate))
	{
		update_animations_and_timer(g);
		handle_player_input(g);
		update_screen(g);
	}
	g->frame_count++;
	return (0);
}

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
