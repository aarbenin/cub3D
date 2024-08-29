/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:16:02 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/29 08:03:33 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/cub3D.h"

/**
 * Checks the adjacent cells around the current position in the map for '0' characters.
 * 
 * @param g Pointer to the game structure containing map data.
 * @param map The map represented as a 2D array of characters.
 * @param i The column index of the current position.
 * @param j The row index of the current position.
 */
static void check_adjacent_walls(t_game *g, char **map, int i, int j)
{
    if (i - 1 >= 0 && i - 1 < (int)ft_strlen(map[j]))
        handle_error(ERR_INV_WALL, g, NULL, map[j][i - 1] == '0');
    if (i + 1 >= 0 && i + 1 < (int)ft_strlen(map[j]))
        handle_error(ERR_INV_WALL, g, NULL, map[j][i + 1] == '0');
}


/**
 * Checks the surrounding cells around the current position in the map for '0' characters.
 * This includes the cells above, below, and on both sides of the current position.
 * 
 * @param g Pointer to the game structure containing map data.
 * @param map The map represented as a 2D array of characters.
 * @param i The column index of the current position.
 * @param j The row index of the current position.
 */
static void check_surrounding_walls(t_game *g, char **map, int i, int j)
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
 * Checks the adjacent cells around the current position in the map for '0' characters.
 * 
 * Verifies that the cells surrounding the specified position in the map do not contain '0',
 * which would indicate an invalid configuration of walls.
 * 
 * @param g Pointer to the game structure containing map data.
 * @param map The map represented as a 2D array of characters.
 * @param i The column index of the current position.
 * @param j The row index of the current position.
 */
void check_walls(t_game *g, char **map, int i, int j)
{
    check_surrounding_walls(g, map, i, j);
}

/**
 * Handles the player direction setting when a player character is found in the map.
 * Ensures that only one player character is defined.
 * 
 * @param g Pointer to the game structure containing player data.
 * @param character The character representing the player direction.
 * @param i The column index of the player character.
 * @param j The row index of the player character.
 */
static void handle_player_direction(t_game *g, char character, int i, int j)
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
 * Valid characters are '0', '1', 'o', and 'c'.
 * 
 * @param character The character to check.
 * @param g Pointer to the game structure for error reporting.
 */
static void check_invalid_character(char character, t_game *g)
{
    if (!ft_strchr("01oc", character))
        handle_error(ERR_INV_CHARAC, g, NULL, 1);
}


/**
 * Checks for valid characters in the map and assigns player information.
 * 
 * Validates the presence of a single player character and ensures all other characters are valid. 
 * Reports errors if multiple players are found, or if invalid characters are encountered. 
 * Also ensures that at least one player character is present in the map.
 * 
 * @param g Pointer to the game structure containing map data.
 * @param map The map represented as a 2D array of characters.
 * @param i The column index of the current position.
 * @param j The row index of the current position.
 */
void check_characters(t_game *g, char **map, int i, int j)
{
    char character = map[j][i];

    if (ft_strchr("NSWE", character))
        handle_player_direction(g, character, i, j);
    else
        check_invalid_character(character, g);
    if (j == g->height - 1 && !g->pl.dir)
        handle_error(ERR_INV_PLAYER, g, NULL, 1);
}

/**
 * Fills a row of the align_map_rows map with characters from the original map.
 * If the original row is shorter than the new width, spaces are added.
 * 
 * @param dest The destination row in the new map.
 * @param src The original row from the map.
 * @param width The width of the new row.
 */
static void fill_row(char *dest, char *src, int width)
{
    int i = 0;
    int src_len = ft_strlen(src);

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
char **alight_map_rows(t_game *g)
{
    char **updated_map = malloc(sizeof(char *) * (g->height + 1));
    int j = 0;

    while (j < g->height)
    {
        updated_map[j] = malloc(sizeof(char) * (g->width + 1));
        fill_row(updated_map[j], g->map[j], g->width);
        j++;
    }
    updated_map[j] = NULL;

    return updated_map;
}

/**
 * Iterates through the map and performs checks on each character.
 * Verifies walls and characters to ensure the map is valid.
 * 
 * @param g Pointer to the game structure containing map data.
 */
void check_elements(t_game *g)
{
    int i, j;

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

