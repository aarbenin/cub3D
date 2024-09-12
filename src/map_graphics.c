/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_graphics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:43:54 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 12:44:06 by aarbenin         ###   ########.fr       */
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
