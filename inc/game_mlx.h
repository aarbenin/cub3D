/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mlx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:56:23 by ogoman            #+#    #+#             */
/*   Updated: 2024/09/12 09:43:44 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_MLX_H
# define GAME_MLX_H
# include "cub3D.h"

/**
 * @brief Structure for storing image information.
 *
 * This structure holds the details of an image, such as its dimensions, data
 * pointers, and pixel parameters.
 * typedef struct s_img
{
    int height;      //Height of the image in pixels. 
    int width;       // Width of the image in pixels. 
    void *i;         // Pointer to the image data (typically used by graphics 
		libraries to manage image memory). 
    char *addr;      // Pointer to the start of the image data. Used for 
		accessing and manipulating individual pixels. 
    int bpp;         // Bits per pixel (bpp). Defines the number of bits 
		used to represent each pixel. 
    int line_len;    // Length of a single image line in bytes. Defines 
		how many bytes are used per row of the image in memory. 
    int endian;      // Byte order (endianness). Defines the byte order 
		in which pixel data is stored. 
} t_img;
*/
typedef struct s_img
{
	int		height;
	int		width;
	void	*i;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

/*Sets the color of a specific pixel at the given coordinates in the image*/
void			put_pixel(t_img *img, int x, int y, int color);

/*Retrieves the color of a specific pixel at the given coordinates in the
image.*/
unsigned int	get_pixel_color(t_img *img, int x, int y);

/* Draws a filled rectangle with a specified color onto an image.*/
void			draw_rectcurrent_angle(t_img *img, t_vector position,
					t_vector dimensions, int color);

/*Copies pixels from one image to another, skipping a specified color.*/
void			mlx_img_to_img(int p[2], t_img img[2], int c1);

/*Checks if the provided file path is valid for an image.*/
int				is_valid_image_path(const char *file_path);

/*Allocates memory for a t_img structure and initializes it.*/
t_img			*create_image_structure(void);

/*Loads an image from a file and initializes the given t_img structure.*/
int				load_image_from_file(void *mlx_ptr, char *file_path,
					t_img *image);

/*Loads an image from a file and creates a t_img structure for it.*/
t_img			*load_img(void *mlx_ptr, char *file_path);

#endif
