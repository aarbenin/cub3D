/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:34:27 by ogoman            #+#    #+#             */
/*   Updated: 2024/09/12 06:33:36 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * Adds an image to the animation list and manages image count.
 *
 * Decrements the animation counter if the image and pointers are valid.
 * If the image is NULL,
 * the function frees the image and sets a flag indicating no more images.
 * Otherwise, it adds
 * the image to the animation list and returns the updated list.
 *
 * @param img Pointer to the image structure.
 * @param anim Pointer to the pointer of the animation list.
 * @param n Pointer to an array of two integers used for managing image count
 * and flags.
 *
 * @return The updated animation list.
 */

t_list	*get_anim(t_img *img, t_list **anim, int (*n)[2])
{
	if (n && anim && *anim && img)
		(*n)[0]--;
	if (!img)
		return (*anim);
	if (!img->i)
	{
		free(img);
		(*n)[1] = 0;
		return (*anim);
	}
	ft_lstadd_back(anim, ft_lstnew(img));
	return (*anim);
}

/**
 * Processes texture definitions and assigns them to the game structure.
 *
 * Splits the input string into components, identifies the texture type
 * (e.g., NO, SO, EA, WE),
 * and loads the corresponding image. If a color definition is detected,
 * it processes the color.
 * If the definition is invalid, it reports an error.
 *
 * @param trim The trimmed line containing texture or color definitions.
 * @param g Pointer to the game structure to store the texture or color
 * information.
 * @param n Pointer to an array of two integers used for managing texture
 * count and flags.
 */

static void	handle_texture(char **dir, t_game *g, int (*n)[2])
{
	if (!ft_strncmp(dir[0], "NO", 3))
		g->tex.n_bak = get_anim(load_img(g->mlx_ptr, dir[1]), &g->tex.n, n);
	else if (!ft_strncmp(dir[0], "SO", 3))
		g->tex.s_bak = get_anim(load_img(g->mlx_ptr, dir[1]), &g->tex.s, n);
	else if (!ft_strncmp(dir[0], "EA", 3))
		g->tex.e_bak = get_anim(load_img(g->mlx_ptr, dir[1]), &g->tex.e, n);
	else if (!ft_strncmp(dir[0], "WE", 3))
		g->tex.w_bak = get_anim(load_img(g->mlx_ptr, dir[1]), &g->tex.w, n);
	else if (!ft_strncmp(dir[0], "DOOR_CLOSED", 12))
		g->tex.door_closed = load_img(g->mlx_ptr, dir[1]);
	else if (!ft_strncmp(dir[0], "DOOR_OPEN", 10))
		g->tex.door_open = load_img(g->mlx_ptr, dir[1]);
	else
		handle_error(ERR_INV_MAP, g, NULL, 1);
}

/**
 * @brief Handles the color initialization for floor and ceiling.
 * 
 * This function checks if the given color identifier is for floor
 ('F') or ceiling ('C').
 * It only processes the color if it has not been set yet. If the
 color is already set, it raises an error.
 * 
 * @param dir Array of strings containing the direction or color identifiers.
 * @param g Pointer to the game structure.
 */
static void	handle_color(char **dir, t_game *g)
{
	if ((!ft_strncmp(dir[0], "F", 2) && g->tex.floor == -1)
		|| (!ft_strncmp(dir[0], "C", 2) && g->tex.ceiling == -1))
	{
		get_cf_color(dir, g);
	}
	else
	{
		handle_error(ERR_INV_MAP, g, NULL, 1);
	}
}

/**
 * @brief Checks and loads texture files based on map configuration.
 * 
 * This function splits the input line to determine if it's a texture
 * or color definition.
 * It then either handles the texture or the color based on the first token.
 * 
 * @param trim The trimmed line containing texture or color information.
 * @param g Pointer to the game structure.
 * @param n Pointer to the texture and map initialization tracking array.
 */
void	check_textures(char *trim, t_game *g, int (*n)[2])
{
	char	**dir;

	dir = ft_split(trim, ' ');
	if (!dir)
	{
		free(trim);
		handle_error(ERR_OUT_OF_MEMORY, g, NULL, 1);
	}
	if (ft_strncmp(dir[0], "NO", 3) == 0
		|| ft_strncmp(dir[0], "SO", 3) == 0
		|| ft_strncmp(dir[0], "EA", 3) == 0
		|| ft_strncmp(dir[0], "WE", 3) == 0
		|| ft_strncmp(dir[0], "DOOR_CLOSED", 11) == 0
		|| ft_strncmp(dir[0], "DOOR_OPEN", 9) == 0)
		handle_texture(dir, g, n);
	else if (ft_strncmp(dir[0], "F", 2) == 0 || ft_strncmp(dir[0], "C", 2) == 0)
		handle_color(dir, g);
	else
		handle_error(ERR_INV_MAP, g, NULL, 1);
	ft_free_matrix(&dir);
}

/**
 * @brief Processes each line of the map file to either load textures or
 * build the map matrix.
 * 
 * This function trims the input line, checks if it contains a texture
 * or map definition,
 * and processes it accordingly. It also updates the game structure's
 * width based on the line length.
 * 
 * @param line The current line being processed.
 * @param g Pointer to the game structure.
 * @param n Pointer to the texture and map initialization tracking array.
 * @param texture_limit Pointer to the limit of texture definitions allowed.
 */
void	process_line(char *line, t_game *g, int (*n)[2], int *texture_limit)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, "\n");
	free(line);
	if (ft_strncmp(trimmed_line, "DOOR_CLOSED", 11) == 0
		|| ft_strncmp(trimmed_line, "DOOR_OPEN", 9) == 0)
		*texture_limit = 8;
	if (trimmed_line && trimmed_line[0] && ++(*n)[0] < *texture_limit)
		check_textures(trimmed_line, g, n);
	else if ((trimmed_line && trimmed_line[0]) || (*n)[0] >= *texture_limit)
		g->map = ft_extend_matrix(g->map, trimmed_line);
	if ((int)ft_strlen(trimmed_line) > g->width)
		g->width = ft_strlen(trimmed_line);
	free(trimmed_line);
}

/**
 * @brief Initializes the map by reading the map file and processing its
 * content.
 * 
 * This function opens the map file, processes each line to either load
 * textures or build the map matrix,
 * and handles errors related to file format, textures, or an empty map.
 * 
 * @param file The path to the map file.
 * @param g Pointer to the game structure.
 */
void	initialize_map(char *file, t_game *g)
{
	char	*line;
	int		texture_limit;
	int		n[2];

	n[0] = -1;
	n[1] = -1;
	texture_limit = 6;
	g->fd = open(file, O_RDONLY);
	handle_error(ERR_INV_FILE, g, file, g->fd < 0);
	line = get_next_line(g->fd);
	while (line != NULL)
	{
		process_line(line, g, &n, &texture_limit);
		line = get_next_line(g->fd);
	}
	handle_error(ERR_EMPTY_FILE, g, NULL, !n[0]);
	handle_error(ERR_INV_TEX, g, NULL, !n[1]);
	g->height = ft_matrixlen(g->map);
}

/**
 * @brief Reads the map file and initializes the map data.
 * 
 * This function serves as an entry point for loading the map from a file.
 * 
 * @param file The path to the map file.
 * @param g Pointer to the game structure.
 */
void	read_map(char *file, t_game *g)
{
	initialize_map(file, g);
}

/**
 * Validates the walls of the map at the specified row and column boundaries.
 *
 * Checks if the map boundaries are correctly defined with walls ('1') and
 * ensures that the
 * boundaries of the map are properly set for both the top/bottom rows and
 * middle rows.
 *
 * @param g Pointer to the game structure containing the map data.
 * @param row The row index being checked.
 * @param col_start The starting column index of the row, after trimming spaces.
 * @param col_end The ending column index of the row, after trimming spaces.
 */

static void	validate_walls(t_game *g, int row, int col_start, int col_end)
{
	if (row == 0 || row == g->height - 1)
	{
		if (col_end - col_start + 1 < 3
			|| g->map[row][col_start] != '1'
			|| g->map[row][col_end] != '1')
		{
			handle_error(ERR_INV_WALL, g, NULL, 1);
		}
	}
	else
	{
		if (col_end > col_start
			&& (g->map[row][col_start] != '1'
			|| g->map[row][col_end] != '1'))
		{
			handle_error(ERR_INV_WALL, g, NULL, 1);
		}
	}
}
/**
 * Validates the entire map for correct boundaries and checks
 * for required elements.
 *
 * Iterates through each row of the map, trims spaces, and validates wall
 * boundaries. Ensures
 * that the map contains all necessary elements and checks for the presence
 * of at least one row.
 *
 * @param g Pointer to the game structure containing the map data.
 */

void	check_map(t_game *g)
{
	int	row;
	int	col_start;
	int	col_end;

	row = 0;
	while (row < g->height)
	{
		trim_spaces(g->map[row], &col_start, &col_end);
		if (col_start > col_end)
			handle_error(ERR_INV_MAP, g, NULL, 1);
		validate_walls(g, row, col_start, col_end);
		row++;
	}
	check_elements(g);
	handle_error(ERR_INV_MAP, g, NULL, g->height == 0);
}
