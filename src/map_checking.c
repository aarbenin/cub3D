/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:16:02 by ogoman            #+#    #+#             */
/*   Updated: 2024/09/12 12:33:54 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * Checks the adjacent cells around the current position in the map for
 * '0' characters.
 * 
 * @param g Pointer to the game structure containing map data.
 * @param map The map represented as a 2D array of characters.
 * @param i The column index of the current position.
 * @param j The row index of the current position.
 */
static void	check_adjacent_walls(t_game *g, char **map, int i, int j)
{
	if (i - 1 >= 0 && i - 1 < (int)ft_strlen(map[j]))
		handle_error(ERR_INV_WALL, g, NULL, map[j][i - 1] == '0');
	if (i + 1 >= 0 && i + 1 < (int)ft_strlen(map[j]))
		handle_error(ERR_INV_WALL, g, NULL, map[j][i + 1] == '0');
}

/**
 * Checks the surrounding cells around the current position in
 * the map for
 * '0' characters.
 * This includes the cells above, below, and on both sides of
 * the current position.
 * 
 * @param g Pointer to the game structure containing map data.
 * @param map The map represented as a 2D array of characters.
 * @param i The column index of the current position.
 * @param j The row index of the current position.
 */
static void	check_surrounding_walls(t_game *g, char **map, int i, int j)
{
	if (j - 1 >= 0 && j - 1 < g->height)
	{
		check_adjacent_walls(g, map, i, j - 1);
		if (i >= 0 && i < (int)ft_strlen(map[j - 1]))
			handle_error(ERR_INV_WALL, g, NULL, map[j - 1][i] == '0');
	}
	check_adjacent_walls(g, map, i, j);
	if (j + 1 >= 0 && j + 1 < g->height)
	{
		check_adjacent_walls(g, map, i, j + 1);
		if (i >= 0 && i < (int)ft_strlen(map[j + 1]))
			handle_error(ERR_INV_WALL, g, NULL, map[j + 1][i] == '0');
	}
}

/**
 * Checks the adjacent cells around the current position in the
 * map for '0' characters.
 * 
 * Verifies that the cells surrounding the specified position
 * in the map do not contain '0',
 * which would indicate an invalid configuration of walls.
 * 
 * @param g Pointer to the game structure containing map data.
 * @param map The map represented as a 2D array of characters.
 * @param i The column index of the current position.
 * @param j The row index of the current position.
 */
void	check_walls(t_game *g, char **map, int i, int j)
{
	check_surrounding_walls(g, map, i, j);
}

/**
 * Checks for valid characters in the map and assigns player information.
 * 
 * Validates the presence of a single player character and ensures all other
 * characters are valid. 
 * Reports errors if multiple players are found, or if invalid characters
 * are encountered. 
 * Also ensures that at least one player character is present in the map.
 * 
 * @param g Pointer to the game structure containing map data.
 * @param map The map represented as a 2D array of characters.
 * @param i The column index of the current position.
 * @param j The row index of the current position.
 */
void	check_characters(t_game *g, char **map, int i, int j)
{
	char	character;

	character = map[j][i];
	if (ft_strchr("NSWE", character))
		handle_player_direction(g, character, i, j);
	else
		check_invalid_character(character, g);
	if (j == g->height - 1 && !g->pl.dir)
		handle_error(ERR_INV_PLAYER, g, NULL, 1);
}

/**
 * Iterates through the map and performs checks on each character.
 * Verifies walls and characters to ensure the map is valid.
 * 
 * @param g Pointer to the game structure containing map data.
 */
void	check_elements(t_game *g)
{
	int	i;
	int	j;

	j = 0;
	while (j < g->height)
	{
		i = 0;
		while (i < g->width)
		{
			if (g->map[j][i] == ' ')
				check_walls(g, g->map, i, j);
			else
				check_characters(g, g->map, i, j);
			i++;
		}
		j++;
	}
}
