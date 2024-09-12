/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:38:04 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 13:20:06 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Calculates the scaling factors and scaled dimensions for an image.
 * 
 * This function computes the scaling ratio needed to fit the source image
 * within the window dimensions while maintaining the aspect ratio. It also
 * calculates the scaled width and height of the image.
 * 
 * @param src_img Pointer to the source image structure.
 * @param win_params Pointer to the window parameters structure.
 * @param params Pointer to the scale parameters structure to store the
 * results.
 */
static void	calculate_scaling(t_img *src_img, t_window_params *win_params,
		t_scale_params *params)
{
	double	scale_x;
	double	scale_y;

	scale_x = (double)win_params->window_width / src_img->width;
	scale_y = (double)win_params->window_height / src_img->height;
	if (scale_x < scale_y)
		params->ratio = scale_x;
	else
		params->ratio = scale_y;
	params->scaled_width = src_img->width * params->ratio;
	params->scaled_height = src_img->height * params->ratio;
}

/**
 * @brief Calculates the offsets required to center the scaled image
 * in the window.
 * 
 * This function computes the offsets to position the scaled image
 * in the center
 * of the window, ensuring that the image is centered horizontally
 * and vertically.
 * 
 * @param win_params Pointer to the window parameters structure.
 * @param params Pointer to the scale parameters structure containing
 * the scaled dimensions.
 */
static void	calculate_offsets(t_window_params *win_params,
		t_scale_params *params)
{
	params->x_offset = (win_params->window_width - params->scaled_width) / 2;
	params->y_offset = (win_params->window_height - params->scaled_height) / 2;
}

/**
 * @brief Copies and scales pixels from the source image to
 * the destination image.
 * 
 * This function scales the source image and copies its pixels
 * to the destination
 * image according to the scaling ratio and calculated offsets.
 * 
 * @param src_img Pointer to the source image structure.
 * @param dst_img Pointer to the destination image structure.
 * @param params Pointer to the scale parameters structure containing
 * scaling details.
 */
static void	copy_pixels(t_img *src_img, t_img *dst_img, t_scale_params *params)
{
	int	x;
	int	y;
	int	src_x;
	int	src_y;

	y = 0;
	while (y < params->scaled_height)
	{
		x = 0;
		while (x < params->scaled_width)
		{
			src_x = (int)(x / params->ratio);
			src_y = (int)(y / params->ratio);
			put_pixel(dst_img, x + params->x_offset, y + params->y_offset,
				get_pixel_color(src_img, src_x, src_y));
			x++;
		}
		y++;
	}
}

/**
 * @brief Scales the source image and copies it to the destination image.
 * 
 * This function performs the entire image scaling
 * process, including calculating
 * scaling factors, offsets, clearing the destination
 * image, and copying scaled
 * pixels from the source image.
 * 
 * @param src_img Pointer to the source image structure.
 * @param dst_img Pointer to the destination image structure.
 * @param win_params Pointer to the window parameters structure.
 */
static void	scale_image(t_img *src_img, t_img *dst_img,
	t_window_params *win_params)
{
	t_scale_params	params;

	calculate_scaling(src_img, win_params, &params);
	calculate_offsets(win_params, &params);
	clear_image(dst_img, win_params->background_color);
	copy_pixels(src_img, dst_img, &params);
}

/**
 * @brief Displays the pause screen by scaling the welcome
 * image to fit the window.
 * 
 * This function creates a new scaled image for the pause
 * screen, clears any
 * existing scaled welcome image, and then displays the scaled
 * image in the
 * window. The image is centered and scaled according to
 * the window dimensions.
 * 
 * @param g Pointer to the game structure.
 */
void	display_pause_screen(t_game *g)
{
	int				window_width;
	int				window_height;
	t_window_params	win_params;

	window_width = g->window_width;
	window_height = g->window_height;
	if (g->scaled_welcome.i)
		mlx_destroy_image(g->mlx_ptr, g->scaled_welcome.i);
	g->scaled_welcome.i = mlx_new_image(g->mlx_ptr, window_width,
			window_height);
	g->scaled_welcome.addr = mlx_get_data_addr(g->scaled_welcome.i,
			&g->scaled_welcome.bpp, &g->scaled_welcome.line_len,
			&g->scaled_welcome.endian);
	win_params.window_width = window_width;
	win_params.window_height = window_height;
	win_params.background_color = 0x091B03;
	scale_image(g->welcome_screen, &g->scaled_welcome, &win_params);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->scaled_welcome.i, 0, 0);
}
