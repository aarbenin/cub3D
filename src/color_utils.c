/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:05:05 by ogoman            #+#    #+#             */
/*   Updated: 2024/09/12 11:15:52 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Parses a string representing a color value and converts it
 * to an integer.
 * 
 * This function reads a string of digits, converts it to a long integer,
 * and checks
 * if the value is within the valid range for a color component (0-255).
 * The function
 * also ensures that the entire string is a valid representation of the
 * number.
 * 
 * @param nptr Pointer to the string containing the color value.
 * @param value Pointer to a long integer where the parsed value will be
 * stored.
 * 
 * @return Returns 0 if the parsing is successful and the value is within
 * range.
 *         Returns -1 if there is an error (e.g., non-digit characters or
 * out-of-range values).
 */
int	parse_color_value(const char *nptr, long *value)
{
	*value = 0;
	if (!nptr || !ft_isdigit(*nptr))
		return (-1);
	while (ft_isdigit(*nptr))
	{
		*value = 10 * (*value) + (*nptr - '0');
		if (*value < 0 || *value > 255)
			return (-1);
		nptr++;
	}
	if (*nptr)
		return (-1);
	return (0);
}

/**
 * @brief Blends two colors based on a given alpha value.
 * 
 * This function takes two RGB colors and blends them using
 * a floating-point alpha, resulting in a smooth transition between the two.
 * 
 * @param color1 First color.
 * @param color2 Second color.
 * @param alpha Blend factor (0.0 to 1.0).
 * @return Blended color.
 */
int	blend_colors(int color1, int color2, float alpha)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color1 >> 16) & 0xFF) * alpha + ((color2 >> 16) & 0xFF) * (1.0
				- alpha));
	g = (int)(((color1 >> 8) & 0xFF) * alpha + ((color2 >> 8) & 0xFF) * (1.0
				- alpha));
	b = (int)((color1 & 0xFF) * alpha + (color2 & 0xFF) * (1.0 - alpha));
	return ((r << 16) | (g << 8) | b);
}
