/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_mlx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:56:23 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/12 06:35:29 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX_H
# define MY_MLX_H
# include "cub3D.h"

typedef struct s_img
{
	int height;	  // Высота изображения
	int width;	  // Ширина изображения
	void *i;	  // Указатель на изображение (обычно для MiniLibX)
	char *addr;	  // Указатель на адрес данных изображения (для доступа к пикселям)
	int bpp;	  // Количество бит на пиксель (bits per pixel)
	int line_len; // Длина строки изображения в байтах
	int endian;	  // Порядок байтов (endianness) изображения
} t_img;

/*Sets the color of a specific pixel at the given coordinates in the image*/
void put_pixel(t_img *img, int x, int y, int color);

/*Retrieves the color of a specific pixel at the given coordinates in the image.*/
unsigned int get_pixel_color(t_img *img, int x, int y);

/* Draws a filled rectangle with a specified color onto an image.*/
void draw_rectcurrent_angle(t_img *img, t_vector position, t_vector dimensions, int color);

/*Copies pixels from one image to another, skipping a specified color.*/
void mlx_img_to_img(int p[2], t_img img[2], int c1);

/*Checks if the provided file path is valid for an image.*/
int is_valid_image_path(const char *file_path);

/*Allocates memory for a t_img structure and initializes it.*/
t_img *create_image_structure(void);

/*Loads an image from a file and initializes the given t_img structure.*/
int load_image_from_file(void *mlx_ptr, char *file_path, t_img *image);

/*Loads an image from a file and creates a t_img structure for it.*/
t_img *load_img(void *mlx_ptr, char *file_path);

#endif
