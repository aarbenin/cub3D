/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:41:20 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 10:13:05 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Calculates the x-coordinate for the texture
 * based on raycasting results.
 *
 * @param tex_params Pointer to the texture parameters structure.
 * @return The calculated x-coordinate for the texture.
 */
static int	calculate_tex_x(t_texture_params *tex_params)
{
	int	tex_x;

	tex_x = (int)(tex_params->params->wall_x
			* (float)tex_params->texture->width);
	if ((tex_params->ray->side == 0 && tex_params->ray->ray_dir_x > 0)
		|| (tex_params->ray->side == 1 && tex_params->ray->ray_dir_y < 0))
		tex_x = tex_params->texture->width - tex_x - 1;
	return (tex_x);
}

/**
 * @brief Draws a vertical line of the texture on the screen at position x.
 *
 * @param g Pointer to the game structure containing the window image.
 * @param x The x-coordinate on the screen where the line should be drawn.
 * @param tex_params Pointer to the texture parameters structure.
 * @param tex_x The x-coordinate on the texture to sample from.
 */
static void	draw_vertical_texture_line(t_game *g, int x,
		t_texture_params *tex_params, int tex_x)
{
	int		y;
	int		tex_y;
	int		color;
	float	step;
	float	tex_pos;

	step = 1.0 * tex_params->texture->height / tex_params->params->line_height;
	tex_pos = (tex_params->params->draw_start - WIN_H / 2
			+ tex_params->params->line_height / 2) * step;
	y = tex_params->params->draw_start;
	while (y < tex_params->params->draw_end)
	{
		tex_y = (int)tex_pos & (tex_params->texture->height - 1);
		tex_pos += step;
		color = get_pixel_color(tex_params->texture, tex_x, tex_y);
		if (tex_params->ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel(&g->win_img, x, y, color);
		y++;
	}
}
/**
 * @brief Draws a textured vertical line on the screen.
 *
 * @param g Pointer to the game structure containing the window image.
 * @param x The x-coordinate on the screen where the line should be drawn.
 * @param texture Pointer to the texture image.
 * @param params Pointer to the drawing parameters (e.g., line
 * height, start/end).
 * @param ray Pointer to the ray data (e.g., direction, side hit).
 */

void	draw_texture_line(t_game *g, int x, t_img *texture,
		t_draw_params *params, t_ray_data *ray)
{
	int					tex_x;
	t_texture_params	tex_params;

	tex_params.texture = texture;
	tex_params.params = params;
	tex_params.ray = ray;
	tex_x = calculate_tex_x(&tex_params);
	draw_vertical_texture_line(g, x, &tex_params, tex_x);
}
