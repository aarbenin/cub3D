/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:41:28 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/11 13:00:15 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Fills a row in the image with a specified color.
 *
 * @param img Pointer to the image structure.
 * @param color Color to fill the row with.
 * @param y The y-coordinate of the row to fill.
 */
static void	fill_row(t_img *img, int color, int y)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		put_pixel(img, x, y, color);
		x++;
	}
}

/**
 * @brief Adjusts the brightness of a given color.
 *
 * @param color The original color.
 * @param factor Brightness adjustment factor (0-255).
 * @return Adjusted color with modified brightness.
 */
static int	adjust_brightness(int color, int factor)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * factor / 255;
	g = ((color >> 8) & 0xFF) * factor / 255;
	b = (color & 0xFF) * factor / 255;
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief Calculates a color gradient based on distance from the horizon.
 *
 * @param base_color The base color to apply the gradient to.
 * @param y The y-coordinate (row) being processed.
 * @param height The total height of the screen.
 * @param is_ceiling Boolean indicating whether the row is part of the ceiling.
 * @return Color adjusted with gradient effect.
 */
static int	calculate_gradient(int base_color, int y, int height,
		int is_ceiling)
{
	double	distance_factor;

	if (is_ceiling)
		distance_factor = 0.5 + 0.5 * (1.0 - ((double)y / (height / 2)));
	else
		distance_factor = 0.5 + 0.5 * (((double)(y - height / 2)) / (height
					/ 2));
	return (adjust_brightness(base_color, (int)(distance_factor * 255)));
}

/**
 * @brief Draws the background by filling the ceiling and floor with
 * gradient colors.
 *
 * @param g Pointer to the game structure containing textures and window data.
 */
void	draw_background(t_game *g)
{
	int	ceiling_color;
	int	floor_color;
	int	y;

	y = 0;
	while (y < WIN_H / 2)
	{
		ceiling_color = calculate_gradient(g->tex.ceiling, y, WIN_H, 1);
		fill_row(&g->win_img, ceiling_color, y);
		y++;
	}
	while (y < WIN_H)
	{
		floor_color = calculate_gradient(g->tex.floor, y, WIN_H, 0);
		fill_row(&g->win_img, floor_color, y);
		y++;
	}
}
