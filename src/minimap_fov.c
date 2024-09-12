/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_fov.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:13:11 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 11:14:22 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Initializes field of view (FOV) parameters for minimap rendering.
 * 
 * This function calculates the starting angle, ending angle, and other
 * necessary parameters to represent the player's FOV on the minimap.
 * 
 * @param g Pointer to the game structure containing player and map info.
 * @return Initialized FOV parameters.
 */
static t_fov_params	init_fov_params(t_game *g)
{
	t_fov_params	params;

	params.fov_length = 20;
	params.fov_angle = 30;
	params.minimap_scale = 5;
	params.player_size = params.minimap_scale;
	params.center_x = (int)(g->pl.position_x * params.minimap_scale
			+ (g->minimap.width - g->width * params.minimap_scale) / 2);
	params.center_y = (int)(g->pl.position_y * params.minimap_scale
			+ (g->minimap.height - g->height * params.minimap_scale) / 2);
	params.color = 0x7F7F4C;
	params.angle_start = atan2(g->pl.dir_y, g->pl.dir_x) - (params.fov_angle
			* M_PI / 180.0);
	params.angle_end = atan2(g->pl.dir_y, g->pl.dir_x) + (params.fov_angle
			* M_PI / 180.0);
	return (params);
}

/**
 * @brief Draws a single line representing part of the FOV.
 * 
 * This function draws a line starting from the player's position
 * and extending
 * outward in the given direction (angle). The line stops if it
 * hits a wall or a door.
 * 
 * @param g Pointer to the game structure.
 * @param params FOV parameters.
 * @param start Starting point (player's position).
 * @param angle The angle of the FOV line.
 */
static void	draw_fov_line(t_game *g, t_fov_params params, t_point start,
		double angle)
{
	t_point	end;
	int		length;

	length = 0;
	while (length < params.fov_length)
	{
		end.x = params.center_x + (int)(cos(angle) * length);
		end.y = params.center_y + (int)(sin(angle) * length);
		if (end.x < 0 || end.y < 0 || end.x >= g->minimap.width
			|| end.y >= g->minimap.height || g->map[end.y
				/ params.minimap_scale][end.x / params.minimap_scale] == '1'
			|| g->map[end.y / params.minimap_scale][end.x
				/ params.minimap_scale] == 'D')
			break ;
		end.color = params.color;
		mlx_draw_line(&g->minimap, start, end);
		length++;
	}
}

/**
 * @brief Draws the field of view (FOV) on the minimap.
 * 
 * This function draws the player's FOV by iterating over the
 * FOV angle range
 * and rendering lines from the player's position outward.
 * 
 * @param g Pointer to the game structure.
 */
void	draw_fov(t_game *g)
{
	t_fov_params	params;
	t_point			start;
	double			angle;

	params = init_fov_params(g);
	start.x = params.center_x + params.player_size / 2;
	start.y = params.center_y + params.player_size / 2;
	start.color = params.color;
	angle = params.angle_start;
	while (angle <= params.angle_end)
	{
		draw_fov_line(g, params, start, angle);
		angle += 0.01;
	}
}
