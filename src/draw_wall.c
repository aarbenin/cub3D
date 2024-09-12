/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:41:05 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 11:18:41 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Calculates the height of the wall line to be drawn based on ray
 * distance.
 *
 * @param ray Pointer to the ray data structure containing raycasting
 * information.
 * @param wall_params Pointer to the wall parameters structure to store the
 * result.
 */
static void	calculate_line_height(t_ray_data *ray, t_wall_params *wall_params)
{
	wall_params->params.line_height = (int)(WIN_H / ray->perp_wall_dist);
	wall_params->params.draw_start = -wall_params->params.line_height / 2
		+ WIN_H / 2;
	if (wall_params->params.draw_start < 0)
		wall_params->params.draw_start = 0;
	wall_params->params.draw_end = wall_params->params.line_height / 2 + WIN_H
		/ 2;
	if (wall_params->params.draw_end >= WIN_H)
		wall_params->params.draw_end = WIN_H - 1;
}

/**
 * @brief Selects the correct texture based on the map cell and ray direction.
 *
 * @param g Pointer to the game structure containing textures and map data.
 * @param ray Pointer to the ray data structure containing raycasting
 * information.
 * @return A pointer to the selected texture image.
 */
static t_img	*select_texture(t_game *g, t_ray_data *ray)
{
	char	cell;

	cell = g->map[ray->map_y][ray->map_x];
	if (cell == 'D')
		return (g->tex.door_closed);
	else if (cell == 'O')
		return (g->tex.door_open);
	else if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return ((t_img *)g->tex.e->content);
		else
			return ((t_img *)g->tex.w->content);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return ((t_img *)g->tex.s->content);
		else
			return ((t_img *)g->tex.n->content);
	}
}

/**
 * @brief Calculates the x-coordinate of the wall hit position on the texture.
 *
 * @param g Pointer to the game structure containing player data.
 * @param ray Pointer to the ray data structure containing raycasting
 * information.
 * @param wall_params Pointer to the wall parameters structure to store
 * the result.
 */
static void	calculate_wall_hit_x(t_game *g, t_ray_data *ray,
		t_wall_params *wall_params)
{
	if (ray->side == 0)
		wall_params->wall_x = g->pl.position_y + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		wall_params->wall_x = g->pl.position_x + ray->perp_wall_dist
			* ray->ray_dir_x;
	wall_params->wall_x -= floor(wall_params->wall_x);
}

/**
 * @brief Draws a vertical line representing a wall segment with the
 * selected texture.
 *
 * @param g Pointer to the game structure containing textures and window
 * data.
 * @param x The x-coordinate on the screen where the line should be drawn.
 * @param ray Pointer to the ray data structure containing raycasting
 * information.
 */
void	draw_wall_line(t_game *g, int x, t_ray_data *ray)
{
	t_wall_params	wall_params;

	calculate_line_height(ray, &wall_params);
	g->additional.texture = select_texture(g, ray);
	calculate_wall_hit_x(g, ray, &wall_params);
	g->additional.params = &wall_params.params;
	g->additional.ray = ray;
	g->additional.params->wall_x = wall_params.wall_x;
	draw_texture_line(g, x);
}
