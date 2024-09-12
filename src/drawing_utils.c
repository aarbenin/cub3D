/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:11:54 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 13:17:52 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Initializes Bresenham's line drawing algorithm parameters.
 * 
 * This function calculates the differences in x and y coordinates
 * and sets the direction of line drawing based on the start and end points.
 * 
 * @param start Starting point of the line.
 * @param end Ending point of the line.
 * @return Initialized Bresenham parameters.
 */
static t_bresenham	init_bresenham(t_point start, t_point end)
{
	t_bresenham	b;

	b.dx = abs(end.x - start.x);
	if (start.x < end.x)
		b.sx = 1;
	else
		b.sx = -1;
	b.dy = -abs(end.y - start.y);
	if (start.y < end.y)
		b.sy = 1;
	else
		b.sy = -1;
	b.err = b.dx + b.dy;
	return (b);
}

/**
 * @brief Draws a line between two points using Bresenham's algorithm.
 * 
 * This function uses Bresenham's line drawing algorithm to efficiently
 * draw a line from the starting point to the ending point, pixel by pixel.
 * 
 * @param img Pointer to the image where the line will be drawn.
 * @param start The starting point of the line.
 * @param end The ending point of the line.
 */
void	mlx_draw_line(t_img *img, t_point start, t_point end)
{
	t_bresenham	b;
	int			e2;

	b = init_bresenham(start, end);
	while (1)
	{
		put_pixel(img, start.x, start.y, start.color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = b.err << 1;
		if (e2 >= b.dy)
		{
			b.err += b.dy;
			start.x += b.sx;
		}
		if (e2 <= b.dx)
		{
			b.err += b.dx;
			start.y += b.sy;
		}
	}
}

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
