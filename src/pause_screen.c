/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:38:04 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/11 11:38:05 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	calculate_scaling(t_img *src_img, t_window_params *win_params,
		t_scale_params *params)
{
	double	scale_x;
	double	scale_y;

	scale_x = (double)win_params->window_width / src_img->width;
	scale_y = (double)win_params->window_height / src_img->height;
	params->ratio = scale_x < scale_y ? scale_x : scale_y;
	params->scaled_width = src_img->width * params->ratio;
	params->scaled_height = src_img->height * params->ratio;
}

static void	calculate_offsets(t_window_params *win_params,
		t_scale_params *params)
{
	params->x_offset = (win_params->window_width - params->scaled_width) / 2;
	params->y_offset = (win_params->window_height - params->scaled_height) / 2;
}

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

static void	scale_image(t_img *src_img, t_img *dst_img, t_window_params *win_params)
{
	t_scale_params	params;

	calculate_scaling(src_img, win_params, &params);
	calculate_offsets(win_params, &params);
	clear_image(dst_img, win_params->background_color);
	copy_pixels(src_img, dst_img, &params);
}

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
