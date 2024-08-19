/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:29:11 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/14 08:34:32 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * Initializes raycasting parameters based on the player's direction.
 *
 * @param g A pointer to a t_text_game structure that contains game state information.
 *
 * This function sets up the initial parameters for raycasting in the game.
 * It determines the current angle of the ray based on the player's direction
 * and sets other raycasting-related parameters such as the horizontal field of view
 * (hfov), angle increment per pixel, precision, and maximum distance for raycasting.
 */
void init_ray(t_text_game *g)
{

	g->ray.current_angle = 0;
	if (g->pl.dir == 'S')
		g->ray.current_angle = 90;
	else if (g->pl.dir == 'W')
		g->ray.current_angle = 180;
	else if (g->pl.dir == 'N')
		g->ray.current_angle = 270;
    g->ray.hfov = 30; //горизонтальное поле зрения (hfov) на 30 градусов.
    g->ray.angle_increment = 2 * g->ray.hfov / WIN_W; // приращение угла на пиксель в зависимости от ширины окна и hfov.
    g->ray.precision = 50; // точность рэйкастинга (частота запуска лучей).
    g->ray.max_distance = 10;  // максимальное расстояние для рэйкастинга.
}
