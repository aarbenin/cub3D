/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:40:24 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/12 06:46:30 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

typedef struct s_minimap_params
{
	int				width;
	int				height;
	int				color;
	int				size;
}					t_minimap_params;

typedef struct s_rect_params
{
	t_vector		position;
	t_vector		dimensions;
	int				color;
}					t_rect_params;

typedef struct s_fov_params
{
	int				fov_length;
	int				fov_angle;
	int				minimap_scale;
	int				player_size;
	int				center_x;
	int				center_y;
	int				color;
	double			angle_start;
	double			angle_end;
}					t_fov_params;

//_________________minimap_border.c_____________________//
/**
 * @brief Draws the corners of the minimap border.
 * 
 * This function draws colored squares at each corner of the minimap
 * to create a visual border effect. It uses double the size of the 
 * minimap's defined border size for a thicker corner.
 * 
 * @param minimap Pointer to the minimap image.
 * @param params Parameters defining the minimap's size and color.
 */
static void	draw_corners(t_img *minimap, t_minimap_params params)
{
	int	i;
	int	j;
	int	color;
	int	size;

	i = 0;
	color = 0x911E1D;
	size = params.size * 2;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(minimap, i, j, color);
			put_pixel(minimap, params.width - 1 - i, j, color);
			put_pixel(minimap, i, params.height - 1 - j, color);
			put_pixel(minimap, params.width - 1 - i, params.height - 1 - j,
				color);
			j++;
		}
		i++;
	}
}
/**
 * @brief Draws the border around the minimap.
 * 
 * This function draws a rectangular border along the edges of the minimap.
 * After drawing the border, it calls `draw_corners` to handle the corner
 * decorations.
 * 
 * @param g Pointer to the game structure containing minimap details.
 */

static void	draw_minimap_border(t_game *g)
{
	int					x;
	int					y;
	int					border_color;
	t_minimap_params	params;

	border_color = 0xFFFFFF;
	params.color = 0xCCCCCC;
	params.size = 3;
	params.width = g->minimap.width;
	params.height = g->minimap.height;
	x = 0;
	while (x < g->minimap.width)
	{
		put_pixel(&g->minimap, x, 0, border_color);
		put_pixel(&g->minimap, x, g->minimap.height - 1, border_color);
		x++;
	}
	y = 0;
	while (y < g->minimap.height)
	{
		put_pixel(&g->minimap, 0, y, border_color);
		put_pixel(&g->minimap, g->minimap.width - 1, y, border_color);
		y++;
	}
	draw_corners(&g->minimap, params);
}

//_________to game_mlx.c_______________________
/**
 * @brief Initializes Bresenham's line drawing algorithm parameters.
 * 
 * This function calculates the differences in x and y coordinates
 * and sets the direction of line drawing based on the start and end points.
 * 
 * @param start Starting point of the line.
 * @param end Ending point of the line.
 * @return Initialized Bresenham parameters.
 */
static t_bresenham	init_bresenham(t_point start, t_point end)
{
	t_bresenham	b;

	b.dx = abs(end.x - start.x);
	if (start.x < end.x)
		b.sx = 1;
	else
		b.sx = -1;
	b.dy = -abs(end.y - start.y);
	if (start.y < end.y)
		b.sy = 1;
	else
		b.sy = -1;
	b.err = b.dx + b.dy;
	return (b);
}

/**
 * @brief Draws a line between two points using Bresenham's algorithm.
 * 
 * This function uses Bresenham's line drawing algorithm to efficiently
 * draw a line from the starting point to the ending point, pixel by pixel.
 * 
 * @param img Pointer to the image where the line will be drawn.
 * @param start The starting point of the line.
 * @param end The ending point of the line.
 */
static void	mlx_draw_line(t_img *img, t_point start, t_point end)
{
	t_bresenham	b;
	int			e2;

	b = init_bresenham(start, end);
	while (1)
	{
		put_pixel(img, start.x, start.y, start.color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = b.err << 1;
		if (e2 >= b.dy)
		{
			b.err += b.dy;
			start.x += b.sx;
		}
		if (e2 <= b.dx)
		{
			b.err += b.dx;
			start.y += b.sy;
		}
	}
}

//___________________minimap_fov.c________________________
/**
 * @brief Initializes field of view (FOV) parameters for minimap rendering.
 * 
 * This function calculates the starting angle, ending angle, and other
 * necessary parameters to represent the player's FOV on the minimap.
 * 
 * @param g Pointer to the game structure containing player and map info.
 * @return Initialized FOV parameters.
 */
static t_fov_params	init_fov_params(t_game *g)
{
	t_fov_params	params;

	params.fov_length = 20;
	params.fov_angle = 30;
	params.minimap_scale = 5;
	params.player_size = params.minimap_scale;
	params.center_x = (int)(g->pl.position_x * params.minimap_scale
			+ (g->minimap.width - g->width * params.minimap_scale) / 2);
	params.center_y = (int)(g->pl.position_y * params.minimap_scale
			+ (g->minimap.height - g->height * params.minimap_scale) / 2);
	params.color = 0x7F7F4C;
	params.angle_start = atan2(g->pl.dir_y, g->pl.dir_x) - (params.fov_angle
			* M_PI / 180.0);
	params.angle_end = atan2(g->pl.dir_y, g->pl.dir_x) + (params.fov_angle
			* M_PI / 180.0);
	return (params);
}

/**
 * @brief Draws a single line representing part of the FOV.
 * 
 * This function draws a line starting from the player's position
 * and extending
 * outward in the given direction (angle). The line stops if it
 * hits a wall or a door.
 * 
 * @param g Pointer to the game structure.
 * @param params FOV parameters.
 * @param start Starting point (player's position).
 * @param angle The angle of the FOV line.
 */
static void	draw_fov_line(t_game *g, t_fov_params params, t_point start,
		double angle)
{
	t_point	end;
	int		length;

	length = 0;
	while (length < params.fov_length)
	{
		end.x = params.center_x + (int)(cos(angle) * length);
		end.y = params.center_y + (int)(sin(angle) * length);
		if (end.x < 0 || end.y < 0 || end.x >= g->minimap.width
			|| end.y >= g->minimap.height || g->map[end.y
				/ params.minimap_scale][end.x / params.minimap_scale] == '1'
			|| g->map[end.y / params.minimap_scale][end.x
				/ params.minimap_scale] == 'D')
			break ;
		end.color = params.color;
		mlx_draw_line(&g->minimap, start, end);
		length++;
	}
}

/**
 * @brief Draws the field of view (FOV) on the minimap.
 * 
 * This function draws the player's FOV by iterating over the
 * FOV angle range
 * and rendering lines from the player's position outward.
 * 
 * @param g Pointer to the game structure.
 */
static void	draw_fov(t_game *g)
{
	t_fov_params	params;
	t_point			start;
	double			angle;

	params = init_fov_params(g);
	start.x = params.center_x + params.player_size / 2;
	start.y = params.center_y + params.player_size / 2;
	start.color = params.color;
	angle = params.angle_start;
	while (angle <= params.angle_end)
	{
		draw_fov_line(g, params, start, angle);
		angle += 0.01;
	}
}

//_____________________color.c_________________________
/**
 * @brief Blends two colors based on a given alpha value.
 * 
 * This function takes two RGB colors and blends them using
 * a floating-point alpha, resulting in a smooth transition between the two.
 * 
 * @param color1 First color.
 * @param color2 Second color.
 * @param alpha Blend factor (0.0 to 1.0).
 * @return Blended color.
 */
int	blend_colors(int color1, int color2, float alpha)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color1 >> 16) & 0xFF) * alpha + ((color2 >> 16) & 0xFF) * (1.0
				- alpha));
	g = (int)(((color1 >> 8) & 0xFF) * alpha + ((color2 >> 8) & 0xFF) * (1.0
				- alpha));
	b = (int)((color1 & 0xFF) * alpha + (color2 & 0xFF) * (1.0 - alpha));
	return ((r << 16) | (g << 8) | b);
}

//_____________________draw_minimap.c_________________________
/**
 * @brief Sets the color of a minimap cell based on the map data.
 * 
 * This function determines the color of a cell on the minimap based
 * on its type,
 * such as walls, doors, or the player's position.
 * 
 * @param g Pointer to the game structure.
 * @param x X-coordinate of the cell.
 * @param y Y-coordinate of the cell.
 * @param color Pointer to the color value that will be set.
 */
static void	set_minimap_color(t_game *g, int x, int y, int *color)
{
	char	cell;

	cell = g->map[y][x];
	if (cell == '1')
		*color = 0xFFFFFF;
	else if (cell == 'D')
		*color = 0xFF0000;
	else if (cell == 'O')
		*color = 0x00FF00;
	else if (y == (int)g->pl.position_y && x == (int)g->pl.position_x)
		*color = 0xFFFF00;
	else
		*color = 0x000000;
}

/**
 * @brief Sets the parameters for drawing a rectangle on the minimap.
 * 
 * This function calculates the position and size of each cell (rectangle)
 * on the minimap based on the minimap's scale and offsets.
 * 
 * @param g Pointer to the game structure.
 * @param params Pointer to the rectangle parameters.
 * @param x X-coordinate of the map cell.
 * @param y Y-coordinate of the map cell.
 */
static void	set_minimap_params(t_game *g, t_rect_params *params, int x, int y)
{
	int	offset_x;
	int	offset_y;

	offset_x = (g->minimap.width - g->width * g->minimap_scale) / 2;
	offset_y = (g->minimap.height - g->height * g->minimap_scale) / 2;
	params->position.x = offset_x + x * g->minimap_scale;
	params->position.y = offset_y + y * g->minimap_scale;
	params->dimensions.x = g->minimap_scale;
	params->dimensions.y = g->minimap_scale;
}

/**
 * @brief Draws a filled rectangle on the minimap with blended colors.
 * 
 * This function fills a rectangle (representing a minimap cell) with a 
 * color, blending it with the background image for a smooth effect.
 * 
 * @param img Pointer to the minimap image.
 * @param params Parameters defining the position, dimensions, and
 * color of the rectangle.
 * @param background_img Pointer to the background image for color blending.
 */
static void	draw_rect(t_img *img, t_rect_params params, t_img *background_img)
{
	int	x;
	int	y;
	int	bg_color;
	int	blended_color;

	y = 0;
	while (y < params.dimensions.y)
	{
		x = 0;
		while (x < params.dimensions.x)
		{
			bg_color = get_pixel_color(background_img, params.position.x + x,
					params.position.y + y);
			blended_color = blend_colors(params.color, bg_color, 0.6);
			put_pixel(img, params.position.x + x, params.position.y + y,
				blended_color);
			x++;
		}
		y++;
	}
}

/**
 * @brief Draws the entire minimap, including FOV and borders.
 * 
 * This function iterates over the map data to draw each cell of the minimap,
 * sets the colors for walls, doors, and player position, and finally
 * draws the 
 * player's field of view (FOV) and the border around the minimap.
 * 
 * @param g Pointer to the game structure.
 */
void	draw_minimap(t_game *g)
{
	int				x;
	int				y;
	int				color;
	t_rect_params	params;

	y = 0;
	while (y < g->height)
	{
		x = 0;
		while (x < g->width)
		{
			set_minimap_color(g, x, y, &color);
			set_minimap_params(g, &params, x, y);
			params.color = color;
			draw_rect(&g->minimap, params, &g->win_img);
			x++;
		}
		y++;
	}
	draw_fov(g);
	draw_minimap_border(g);
}
