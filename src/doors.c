/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:41:45 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/17 08:30:41 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Checks if the player is standing in a doorway.
 * 
 * This function checks the player's current position on the map
 * and determines whether the player is in a doorway by comparing
 * the player's coordinates to the map grid. 
 * 
 * @param g Pointer to the game structure.
 * @return true if the player is in a doorway ('O'), false otherwise.
 */

static bool	is_player_in_doorway(t_game *g)
{
	int	player_x;
	int	player_y;

	player_x = (int)g->pl.position_x;
	player_y = (int)g->pl.position_y;
	if (g->map[player_y][player_x] == 'O')
	{
		return (true);
	}
	return (false);
}
/**
 * @brief Toggles the state of a door and checks for player collision.
 * 
 * This function checks the position of a door on the map and toggles 
 * its state between open ('O') and closed ('D'). It also checks if 
 * the player is inside the doorway when closing the door, triggering 
 * a game over if the player is caught inside the door.
 * 
 * @param g Pointer to the game structure.
 * @param door_x X-coordinate of the door.
 * @param door_y Y-coordinate of the door.
 * @return 1 if the door state was changed, 0 otherwise.
 */

static int	check_door(t_game *g, int door_x, int door_y)
{
	if (door_x >= 0 && door_x < g->width && door_y >= 0 && door_y < g->height)
	{
		if (g->map[door_y][door_x] == 'O' && is_player_in_doorway(g))
		{
			printf("\nDumb ways to die... "
				"You closed the door on yourself! Game over.\n\n");
			cleanup_game(g);
			exit(0);
		}
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
