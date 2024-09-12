/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:10:29 by ogoman            #+#    #+#             */
/*   Updated: 2024/09/11 12:59:31 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * Creates a ARGB color value from individual color components (alpha, red,
 * green, blue).
 * 
 * @param color The t_color structure containing the color components.
 * @return The color value in ARGB format.
 */

int	argb_from_color(t_color color)
{
	return (color.alpha << 24 | color.red << 16
		| color.green << 8 | color.blue);
}

/**
 * Extracts the color components from a ARGB color value.
 * 
 * @param color_value The color value in ARGB format.
 * @return The t_color structure with extracted color components.
 */

t_color	color_from_argb(int color_value)
{
	t_color	color;

	color.alpha = (color_value >> 24) & 0xFF;
	color.red = (color_value >> 16) & 0xFF;
	color.green = (color_value >> 8) & 0xFF;
	color.blue = color_value & 0xFF;
	return (color);
}

/**
 * Updates the floor or ceiling color in the game structure based on the
 * provided color string.
 * 
 * @param dir An array of strings containing the color type (floor or ceiling)
 * and the color components.
 * @param g A pointer to the t_game structure that contains texture data.
 */

void	get_cf_color(char **dir, t_game *g)
{
	char	**fc;
	int		floor_or_ceiling[2];
	int		color_values[3];
	t_color	map_color;

	map_color.alpha = 0;
	floor_or_ceiling[0] = !ft_strncmp(dir[0], "F", 2);
	floor_or_ceiling[1] = !ft_strncmp(dir[0], "C", 2);
	fc = ft_split(dir[1], ',');
	if (!fc || ft_matrixlen(fc) != 3)
	{
		ft_free_matrix(&fc);
		return ;
	}
	color_values[0] = parse_color_value(fc[0], &map_color.red);
	color_values[1] = parse_color_value(fc[1], &map_color.green);
	color_values[2] = parse_color_value(fc[2], &map_color.blue);
	ft_free_matrix(&fc);
	if (color_values[0] || color_values[1] || color_values[2])
		return ;
	if (floor_or_ceiling[0])
		g->tex.floor = argb_from_color(map_color);
	else if (floor_or_ceiling[1])
		g->tex.ceiling = argb_from_color(map_color);
}

/**
 * Inverts the colors of the image in the window.
 * 
 * @param g A pointer to the t_game structure containing the window image data.
 */

void	cub_invert_color(t_game *g)
{
	int	xy[2];

	xy[1] = -1;
	while (++xy[1] < WIN_H)
	{
		xy[0] = -1;
		while (++xy[0] < WIN_W)
		{
			put_pixel(&g->win_img, xy[0], xy[1],
				0xFFFFFF - get_pixel_color(&g->win_img, xy[0], xy[1]));
		}
	}
}

/**
 * Calculates the color based on distance and transparency.
 * 
 * @param base_color The base color value.
 * @param dist_from_camera The distance from the camera.
 * @param transparency Flag indicating transparency.
 * @return The color value adjusted for distance and transparency.
 */

int	get_dist_color(int base_color, float dist_from_camera, int transparency)
{
	t_color	color;
	float	diff;

	if (dist_from_camera < 0)
		dist_from_camera = 0;
	diff = powf(1.14, dist_from_camera / 7.5);
	color = color_from_argb(base_color);
	if (transparency)
		color.alpha -= (int)diff;
	else
		color.alpha = 256;
	color.red -= (int)diff;
	color.green -= (int)diff;
	color.blue -= (int)diff;
	if (color.alpha < 0)
		color.alpha = 0;
	if (color.red < 0)
		color.red = 0;
	if (color.green < 0)
		color.green = 0;
	if (color.blue < 0)
		color.blue = 0;
	return (argb_from_color(color));
}
