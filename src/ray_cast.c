/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:36:49 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/17 08:08:02 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Calculates the step direction and initial side distances for the ray.
 * 
 * This function determines the step direction (either -1 or 1) along the x
 * and y axes 
 * based on the ray's direction. It also calculates the initial side distances
 * (the 
 * distance the ray has to travel to the first x or y side of the map) using
 * the player's 
 * current position and the ray's direction.
 * 
 * @param g Pointer to the game structure.
 * @param ray Pointer to the ray data structure.
 * @param delta_dist_x The distance to the next x side of the map.
 * @param delta_dist_y The distance to the next y side of the map.
 */

static inline void	calculate_ray_steps(t_game *g, t_ray_data *ray,
		double delta_dist_x, double delta_dist_y)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (g->pl.position_x - ray->map_x) * delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - g->pl.position_x) * delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (g->pl.position_y - ray->map_y) * delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - g->pl.position_y) * delta_dist_y;
	}
}

/**
 * @brief Calculates the perpendicular distance to the wall hit by the ray.
 * 
 * This function computes the perpendicular distance from the player to the 
 * wall that was hit by the ray. The distance is used for rendering the correct
 * height of the wall slice on the screen.
 * 
 * @param g Pointer to the game structure.
 * @param ray Pointer to the ray data structure.
 */
static inline void	calculate_wall_dist(t_game *g, t_ray_data *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - g->pl.position_x + (1 - ray->step_x)
				/ 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - g->pl.position_y + (1 - ray->step_y)
				/ 2) / ray->ray_dir_y;
}

/**
 * @brief Calculates the delta distances for the ray.
 * 
 * Delta distances represent how far the ray has to travel to cross a grid
 * line 
 * on the x or y axis. These values are calculated based on the ray's
 * direction. 
 * The calculation is done by inverting the ray direction and taking
 * the absolute value.
 * 
 * @param ray Pointer to the ray data structure.
 * @param delta_dist_x Pointer to the delta distance for the x axis.
 * @param delta_dist_y Pointer to the delta distance for the y axis.
 */
static inline void	calculate_delta_dist(t_ray_data *ray, double *delta_dist_x,
		double *delta_dist_y)
{
	*delta_dist_x = 1.0 / (fabs(ray->ray_dir_x) + 1e-9);
	*delta_dist_y = 1.0 / (fabs(ray->ray_dir_y) + 1e-9);
}

/**
 * @brief Casts rays across the screen for rendering.
 * 
 * This function loops through each vertical stripe on the screen and
 * casts a 
 * ray for each one. The ray is cast based on the player's direction
 * and camera 
 * plane. The function calculates the delta distances, steps, and wall
 * distances 
 * for each ray, and then performs Digital Differential Analysis (DDA)
 * to determine 
 * which grid cell the ray hits. After that, it calls the function to
 * draw the 
 * corresponding wall slice.
 * 
 * @param g Pointer to the game structure.
 */
void	cast_rays(t_game *g)
{
	t_ray_data	ray;
	int			x;
	double		camera_x;
	double		delta_dist_x;
	double		delta_dist_y;

	x = 0;
	while (x < WIN_W)
	{
		camera_x = 2 * x / (double)WIN_W - 1;
		ray.ray_dir_x = g->pl.dir_x + g->pl.plane_x * camera_x;
		ray.ray_dir_y = g->pl.dir_y + g->pl.plane_y * camera_x;
		ray.map_x = (int)g->pl.position_x;
		ray.map_y = (int)g->pl.position_y;
		calculate_delta_dist(&ray, &delta_dist_x, &delta_dist_y);
		calculate_ray_steps(g, &ray, delta_dist_x, delta_dist_y);
		perform_dda(g, &ray, delta_dist_x, delta_dist_y);
		calculate_wall_dist(g, &ray);
		draw_wall_line(g, x, &ray);
		x++;
	}
}
