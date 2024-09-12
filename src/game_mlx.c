/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 08:32:41 by ogoman            #+#    #+#             */
/*   Updated: 2024/09/12 11:55:44 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * Sets the color of a specific pixel at the given coordinates in the image.
 *
 * @param img Pointer to the t_img structure representing the image.
 * @param x X-coordinate of the pixel to set.
 * @param y Y-coordinate of the pixel to set.
 * @param color Color to set the pixel to.
 */
void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel_location;

	pixel_location = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel_location = color;
}

/**
 * Retrieves the color of a specific pixel at the given coordinates in the image.
 *
 * @param img Pointer to the t_img structure representing the image.
 * @param x X-coordinate of the pixel to retrieve.
 * @param y Y-coordinate of the pixel to retrieve.
 * @return The color of the pixel at the specified coordinates.
 */
unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	char	*pixel_location;

	pixel_location = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)pixel_location);
}

/**
 * Draws a filled rectangle with a specified color onto an image.
 *
 * @param img Pointer to the t_img structure representingthe
 * destination image.
 * @param position The coordinates (x, y) of the top-left corner of
 * the rectangle.
 * @param dimensions The width and height of the rectangle.
 * @param color Color to fill the rectangle with.
 */
void	draw_rectcurrent_angle(t_img *img, t_vector position,
	t_vector dimensions, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < dimensions.y)
	{
		x = 0;
		while (x < dimensions.x)
		{
			put_pixel(img, position.x + x, position.y + y, color);
			x++;
		}
		y++;
	}
}

/**
 * Copies pixels from one image to another, skipping a specified color.
 *
 * @param offset Array containing the x and y offsets for positioning the
 * source image on the destination image.
 * @param images Array containing two t_img structures: the source image
 * and the destination image.
 * @param color_to_skip Color to exclude from copying.
 */
void	mlx_img_to_img(int p[2], t_img img[2], int c1)
{
	int	xy[2];
	int	color;

	xy[1] = 0;
	while (xy[1] < img[0].height)
	{
		xy[0] = 0;
		while (xy[0] < img[0].width)
		{
			if (xy[0] + p[0] >= 0 && xy[1] + p[1] >= 0)
			{
				color = get_pixel_color(&img[0], xy[0], xy[1]);
				if (color != c1)
				{
					put_pixel(&img[1], xy[0] + p[0], xy[1] + p[1], color);
				}
			}
			xy[0]++;
		}
		xy[1]++;
	}
}
