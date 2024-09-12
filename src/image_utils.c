/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:56:19 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 11:56:21 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * Checks if the provided file path is valid for an image.
 *
 * @param file_path The path to the image file.
 * @return 1 if the path is valid (i.e., ends with ".xpm"), otherwise 0.
 */
int	is_valid_image_path(const char *file_path)
{
	return (file_path && ft_strrncmp(file_path, ".xpm", 4) == 0);
}

/**
 * Allocates memory for a t_img structure and initializes it.
 *
 * @return A pointer to the newly allocated t_img structure,
 * or NULL if memory allocation fails.
 */
t_img	*create_image_structure(void)
{
	t_img	*image;

	image = malloc(sizeof(t_img));
	if (!image)
		return (NULL);
	image->i = NULL;
	return (image);
}

/**
 * Loads an image from a file and initializes the given t_img
 * structure.
 *
 * @param mlx_ptr Pointer to the MLX (MiniLibX) instance used to
 * load the image.
 * @param file_path Path to the image file.
 * @param image Pointer to the t_img structure to be initialized
 * with the image data.
 * @return 1 if the image is successfully loaded, otherwise 0.
 */
int	load_image_from_file(void *mlx_ptr, char *file_path, t_img *image)
{
	image->i = mlx_xpm_file_to_image(mlx_ptr, file_path,
			&image->width, &image->height);
	if (!image->i)
		return (0);
	image->addr = mlx_get_data_addr(image->i, &image->bpp,
			&image->line_len, &image->endian);
	return (1);
}

/**
 * Loads an image from a file and creates a t_img structure for it.
 *
 * @param mlx_ptr Pointer to the MLX (MiniLibX) instance used
 * for loading the image.
 * @param file_path Path to the image file (must be in .xpm format).
 * @return A pointer to a t_img structure containing the image
 * data, or NULL if the image cannot be loaded.
 */
t_img	*load_img(void *mlx_ptr, char *file_path)
{
	int		file_descriptor;
	t_img	*image;

	if (!is_valid_image_path(file_path))
		return (NULL);
	file_descriptor = open(file_path, O_RDONLY);
	if (file_descriptor < 0)
		return (NULL);
	close(file_descriptor);
	image = create_image_structure();
	if (!image)
		return (NULL);
	if (!load_image_from_file(mlx_ptr, file_path, image))
	{
		free(image);
		return (NULL);
	}
	return (image);
}
