/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:34:24 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 12:35:13 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * Handles the player direction setting when a player
 * character is found in the map.
 * Ensures that only one player character is defined.
 * 
 * @param g Pointer to the game structure containing player data.
 * @param character The character representing the player direction.
 * @param i The column index of the player character.
 * @param j The row index of the player character.
 */
void	handle_player_direction(t_game *g, char character, int i, int j)
{
	if (!g->pl.dir)
	{
		g->pl.dir = character;
		g->pl.position_x = (float)i;
		g->pl.position_y = (float)j;
	}
	else
	{
		handle_error(ERR_INV_PLAYER, g, NULL, 1);
	}
}

/**
 * Checks if a character in the map is valid.
 * Valid characters are '0', '1', 'O', and 'D'.
 * 
 * @param character The character to check.
 * @param g Pointer to the game structure for error reporting.
 */
void	check_invalid_character(char character, t_game *g)
{
	if (!ft_strchr("01DO", character))
		handle_error(ERR_INV_CHARAC, g, NULL, 1);
}

/**
 * Fills a row of the align_map_rows map with characters from the original map.
 * If the original row is shorter than the new width, spaces are added.
 * 
 * @param dest The destination row in the new map.
 * @param src The original row from the map.
 * @param width The width of the new row.
 */
static void	fill_row(char *dest, char *src, int width)
{
	int	i;
	int	src_len;

	i = 0;
	src_len = ft_strlen(src);
	while (i < width)
	{
		if (i >= src_len)
			dest[i] = ' ';
		else
			dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

/**
 * Creates a new align_map_rows map with the specified width and height.
 * Pads each row with spaces if it is shorter than the new width.
 * 
 * @param g Pointer to the game structure containing map data.
 * @return A new align_map_rows map represented as a 2D array of characters.
 */
char	**alight_map_rows(t_game *g)
{
	char	**updated_map;
	int		j;

	updated_map = malloc(sizeof(char *) * (g->height + 1));
	j = 0;
	while (j < g->height)
	{
		updated_map[j] = malloc(sizeof(char) * (g->width + 1));
		fill_row(updated_map[j], g->map[j], g->width);
		j++;
	}
	updated_map[j] = NULL;
	return (updated_map);
}
