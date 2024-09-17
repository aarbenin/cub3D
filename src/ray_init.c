/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:36:40 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/17 08:09:22 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Sets initial parameters for raycasting.
 * 
 * This function initializes the parameters related to raycasting,
 * including the
 * horizontal field of view (hfov), the angle increment between rays, 
 * the precision 
 * of raycasting, and the maximum distance a ray will check for collisions.
 * 
 * @param ray Pointer to the ray structure to initialize.
 */
static void	set_ray_params(t_ray *ray)
{
	ray->hfov = 30;
	ray->angle_increment = 2 * ray->hfov / WIN_W;
	ray->precision = 50;
	ray->max_distance = 10;
}

/**
 * @brief Initializes raycasting parameters and player direction.
 * 
 * This function sets up the initial parameters for raycasting and updates 
 * the player's
 * direction based on the game's state. It ensures that the ray parameters 
 * are set
 * appropriately and that the player's direction is correctly initialized.
 * 
 * @param g Pointer to the game structure containing player and ray data.
 */
void	init_ray(t_game *g)
{
	set_player_direction(&g->pl, g->pl.dir);
	set_ray_params(&g->ray);
}
