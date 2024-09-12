/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:41:45 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/11 12:59:48 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * Checks and toggles the state of a door at the given coordinates.
 * 
 * If the door is found in the closed state ('D'), it is opened ('O'). If it is 
 * found in the open state ('O'), it is closed ('D').
 *
 * @param g The game structure containing the map and game state.
 * @param door_x The x-coordinate of the door on the map.
 * @param door_y The y-coordinate of the door on the map.
 * @return 1 if a door was toggled, 0 otherwise.
 */
static int	check_door(t_game *g, int door_x, int door_y)
{
	if (door_x >= 0 && door_x < g->width && door_y >= 0 && door_y < g->height)
	{
		if (g->map[door_y][door_x] == 'D')
		{
			g->map[door_y][door_x] = 'O';
			return (1);
		}
		else if (g->map[door_y][door_x] == 'O')
		{
			g->map[door_y][door_x] = 'D';
			return (1);
		}
	}
	return (0);
}
/**
 * Attempts to find and toggle the nearest door in front of the player.
 * 
 * This function checks in the direction the player is facing for a door within
 * a certain distance. If a door is found, it toggles its state (open/closed).
 *
 * @param g The game structure containing the player and map data.
 */

void	action_door(t_game *g)
{
	double	check_distance;
	double	step;
	double	current_distance;
	int		door_x;
	int		door_y;

	check_distance = 2.5;
	step = 0.2;
	current_distance = 0.0;
	while (current_distance <= check_distance)
	{
		door_x = (int)(g->pl.position_x + g->pl.dir_x * current_distance);
		door_y = (int)(g->pl.position_y + g->pl.dir_y * current_distance);
		if (check_door(g, door_x, door_y))
			break ;
		current_distance += step;
	}
}
