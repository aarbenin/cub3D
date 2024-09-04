/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alisa <alisa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:33:07 by ogoman            #+#    #+#             */
/*   Updated: 2024/09/03 06:19:25 by alisa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

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

int	cub_update(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (!(g->nframes % g->rate))
	{
		if (!(g->nframes % (2 * g->rate)))
			update_anim(g);
		if (!(g->nframes % (10 * g->rate)))
			g->pl.door_cooldown = 0;
		// Очистка перед рендерингом
		clear_image(&g->win_img, 0x000000);
		if (g->pl.keys.w_pressed || g->pl.keys.a_pressed || g->pl.keys.s_pressed
			|| g->pl.keys.d_pressed || g->pl.keys.left_pressed
			|| g->pl.keys.right_pressed)
		{
			move_player(g);
			rotate_player(g);
		}
		draw_background(g);
		// Выполняем Ray-Casting и рендерим сцену
		cast_rays(g);
		redraw_elem(g, *g->scope, WIN_W / 2 - g->scope->width / 2, WIN_H / 2
			- g->scope->height / 2);
		// Отрисовка основной сцены
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->win_img.i, 0, 0);
		// Отрисовка миникарты (в конце, чтобы она оставалась видимой)
		draw_minimap(g);
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->minimap.i, 10, 10);
	}
	g->frame_count++;
	return (0);
}

/**
 * Redraws an image element onto the game window at specified coordinates.
 *

	* @param g A pointer to a t_text_game structure that contains game state information.
 * @param img The image to be drawn.
 * @param x The x-coordinate where the image should be placed.
 * @param y The y-coordinate where the image should be placed.
 *

	* This function places the specified image onto the game window at the given coordinates,

	* combining it with the existing window image. It uses a blending color of 0xFF000000
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
