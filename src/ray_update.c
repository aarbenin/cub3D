/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:36:27 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/17 08:10:59 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Updates the position of the ray during the DDA algorithm.
 * 
 * This function updates the ray's position by incrementing the distance to
 * the next
 * vertical or horizontal grid line. It determines which side (vertical or
 * horizontal) 
 * the ray should move towards based on the current side distances and
 * updates the 
 * map coordinates accordingly.
 * 
 * @param ray Pointer to the ray data structure.
 * @param delta_x Distance to the next vertical grid line.
 * @param delta_y Distance to the next horizontal grid line.
 */
static inline void	update_ray_pos(t_ray_data *ray, double delta_x,
		double delta_y)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += delta_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += delta_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}
/**
 * @brief Checks if the ray has hit a wall or door.
 * 
 * This function checks the current map cell that the ray is pointing to.
 * It determines
 * if the ray has hit a wall ('1') or a door ('D').
 * 
 * @param g Pointer to the game structure.
 * @param ray Pointer to the ray data structure.
 * @return True if the ray has hit a wall or door, otherwise false.
 */

static inline bool	check_hit(t_game *g, t_ray_data *ray)
{
	char	cell;

	cell = g->map[ray->map_y][ray->map_x];
	return (cell == '1' || cell == 'D');
}
/**
 * @brief Performs the DDA (Digital Differential Analyzer) algorithm for
 * raycasting.
 * 
 * This function uses the DDA algorithm to trace a ray through the map.
 * It updates the
 * ray's position step-by-step until it hits a wall or door, checking
 * for collisions
 * at each step.
 * 
 * @param g Pointer to the game structure.
 * @param ray Pointer to the ray data structure.
 * @param delta_x Distance to the next vertical grid line.
 * @param delta_y Distance to the next horizontal grid line.
 */

void	perform_dda(t_game *g, t_ray_data *ray, double delta_x, double delta_y)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		update_ray_pos(ray, delta_x, delta_y);
		hit = check_hit(g, ray);
	}
}
