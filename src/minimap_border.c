/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_border.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:02:02 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 11:04:38 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Draws the corners of the minimap border.
 * 
 * This function draws colored squares at each corner of the minimap
 * to create a visual border effect. It uses double the size of the 
 * minimap's defined border size for a thicker corner.
 * 
 * @param minimap Pointer to the minimap image.
 * @param params Parameters defining the minimap's size and color.
 */
static void	draw_corners(t_img *minimap, t_minimap_params params)
{
	int	i;
	int	j;
	int	color;
	int	size;

	i = 0;
	color = 0x911E1D;
	size = params.size * 2;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(minimap, i, j, color);
			put_pixel(minimap, params.width - 1 - i, j, color);
			put_pixel(minimap, i, params.height - 1 - j, color);
			put_pixel(minimap, params.width - 1 - i, params.height - 1 - j,
				color);
			j++;
		}
		i++;
	}
}
/**
 * @brief Draws the border around the minimap.
 * 
 * This function draws a rectangular border along the edges of the minimap.
 * After drawing the border, it calls `draw_corners` to handle the corner
 * decorations.
 * 
 * @param g Pointer to the game structure containing minimap details.
 */

void	draw_minimap_border(t_game *g)
{
	int					x;
	int					y;
	int					border_color;
	t_minimap_params	params;

	border_color = 0xFFFFFF;
	params.color = 0xCCCCCC;
	params.size = 3;
	params.width = g->minimap.width;
	params.height = g->minimap.height;
	x = 0;
	while (x < g->minimap.width)
	{
		put_pixel(&g->minimap, x, 0, border_color);
		put_pixel(&g->minimap, x, g->minimap.height - 1, border_color);
		x++;
	}
	y = 0;
	while (y < g->minimap.height)
	{
		put_pixel(&g->minimap, 0, y, border_color);
		put_pixel(&g->minimap, g->minimap.width - 1, y, border_color);
		y++;
	}
	draw_corners(&g->minimap, params);
}
