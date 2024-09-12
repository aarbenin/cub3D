/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:37:13 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 06:58:28 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Sets the player's direction and view plane based on the given
 * direction character.
 * 
 * This function updates the player's direction vector and view plane vector
 * depending on the specified direction character ('N', 'S', 'E', 'W').
 * 
 * @param pl Pointer to the player structure that will be updated.
 * @param dir Character indicating the desired direction
 * ('N' for North, 'S' for South, 'E' for East, 'W' for West).
 */
static void	set_direction_north(t_player *pl)
{
	pl->dir_x = 0;
	pl->dir_y = -1;
	pl->plane_x = 0.66;
	pl->plane_y = 0;
}

static void	set_direction_south(t_player *pl)
{
	pl->dir_x = 0;
	pl->dir_y = 1;
	pl->plane_x = -0.66;
	pl->plane_y = 0;
}

static void	set_direction_east(t_player *pl)
{
	pl->dir_x = 1;
	pl->dir_y = 0;
	pl->plane_x = 0;
	pl->plane_y = 0.66;
}

static void	set_direction_west(t_player *pl)
{
	pl->dir_x = -1;
	pl->dir_y = 0;
	pl->plane_x = 0;
	pl->plane_y = -0.66;
}

void	set_player_direction(t_player *pl, char dir)
{
	if (dir == 'N')
		set_direction_north(pl);
	else if (dir == 'S')
		set_direction_south(pl);
	else if (dir == 'E')
		set_direction_east(pl);
	else if (dir == 'W')
		set_direction_west(pl);
}
