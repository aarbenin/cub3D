/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:40:24 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 11:19:45 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Sets the color of a minimap cell based on the map data.
 * 
 * This function determines the color of a cell on the minimap based
 * on its type,
 * such as walls, doors, or the player's position.
 * 
 * @param g Pointer to the game structure.
 * @param x X-coordinate of the cell.
 * @param y Y-coordinate of the cell.
 * @param color Pointer to the color value that will be set.
 */
static void	set_minimap_color(t_game *g, int x, int y, int *color)
{
	char	cell;

	cell = g->map[y][x];
	if (cell == '1')
		*color = 0xFFFFFF;
	else if (cell == 'D')
		*color = 0xFF0000;
	else if (cell == 'O')
		*color = 0x00FF00;
	else if (y == (int)g->pl.position_y && x == (int)g->pl.position_x)
		*color = 0xFFFF00;
	else
		*color = 0x000000;
}

/**
 * @brief Sets the parameters for drawing a rectangle on the minimap.
 * 
 * This function calculates the position and size of each cell (rectangle)
 * on the minimap based on the minimap's scale and offsets.
 * 
 * @param g Pointer to the game structure.
 * @param params Pointer to the rectangle parameters.
 * @param x X-coordinate of the map cell.
 * @param y Y-coordinate of the map cell.
 */
static void	set_minimap_params(t_game *g, t_rect_params *params, int x, int y)
{
	int	offset_x;
	int	offset_y;

	offset_x = (g->minimap.width - g->width * g->minimap_scale) / 2;
	offset_y = (g->minimap.height - g->height * g->minimap_scale) / 2;
	params->position.x = offset_x + x * g->minimap_scale;
	params->position.y = offset_y + y * g->minimap_scale;
	params->dimensions.x = g->minimap_scale;
	params->dimensions.y = g->minimap_scale;
}

/**
 * @brief Draws a filled rectangle on the minimap with blended colors.
 * 
 * This function fills a rectangle (representing a minimap cell) with a 
 * color, blending it with the background image for a smooth effect.
 * 
 * @param img Pointer to the minimap image.
 * @param params Parameters defining the position, dimensions, and
 * color of the rectangle.
 * @param background_img Pointer to the background image for color blending.
 */
static void	draw_rect(t_img *img, t_rect_params params, t_img *background_img)
{
	int	x;
	int	y;
	int	bg_color;
	int	blended_color;

	y = 0;
	while (y < params.dimensions.y)
	{
		x = 0;
		while (x < params.dimensions.x)
		{
			bg_color = get_pixel_color(background_img, params.position.x + x,
					params.position.y + y);
			blended_color = blend_colors(params.color, bg_color, 0.6);
			put_pixel(img, params.position.x + x, params.position.y + y,
				blended_color);
			x++;
		}
		y++;
	}
}

/**
 * @brief Draws the entire minimap, including FOV and borders.
 * 
 * This function iterates over the map data to draw each cell of the minimap,
 * sets the colors for walls, doors, and player position, and finally
 * draws the 
 * player's field of view (FOV) and the border around the minimap.
 * 
 * @param g Pointer to the game structure.
 */
void	draw_minimap(t_game *g)
{
	int				x;
	int				y;
	int				color;
	t_rect_params	params;

	y = 0;
	while (y < g->height)
	{
		x = 0;
		while (x < g->width)
		{
			set_minimap_color(g, x, y, &color);
			set_minimap_params(g, &params, x, y);
			params.color = color;
			draw_rect(&g->minimap, params, &g->win_img);
			x++;
		}
		y++;
	}
	draw_fov(g);
	draw_minimap_border(g);
}
