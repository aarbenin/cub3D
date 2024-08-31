#include "../inc/cub3D.h"

int blend_colors(int color1, int color2, float alpha)
{
	int r = (int)(((color1 >> 16) & 0xFF) * alpha + ((color2 >> 16) & 0xFF) * (1.0 - alpha));
	int g = (int)(((color1 >> 8) & 0xFF) * alpha + ((color2 >> 8) & 0xFF) * (1.0 - alpha));
	int b = (int)((color1 & 0xFF) * alpha + (color2 & 0xFF) * (1.0 - alpha));
	return (r << 16) | (g << 8) | b;
}


static void draw_rect(t_img *img, t_vector position, t_vector dimensions, int color, t_img *background_img)
{
	int x;
	int y;

	y = 0;
	while (y < dimensions.y)
	{
		x = 0;
		while (x < dimensions.x)
		{
			int bg_color = get_pixel_color(background_img, position.x + x, position.y + y);
			int blended_color = blend_colors(color, bg_color, 0.6); // 0.5 - полупрозрачность
			put_pixel(img, position.x + x, position.y + y, blended_color);
			x++;
		}
		y++;
	}
}


static void set_minimap_color(t_game *g, int x, int y, int *color)
{
	char	cell;
	
	cell = g->map[y][x];
	if (cell == '1')
		*color = 0xFFFFFF; // Белый для стен
	else if (cell == 'D')
		*color = 0xFF0000; // Красный для закрытых дверей
	else if (cell == 'O')
		*color = 0x00FF00; // Зеленый для открытых дверей
	else if (y == (int)g->pl.position_y && x == (int)g->pl.position_x)
		*color = 0xFFFF00; // Жёлтый для игрока
	else
		*color = 0x000000; // Черный для пустых клеток
}

static void draw_minimap_border(t_game *g)
{
	int x;
	int y;
	int i;
	int j;
	int border_color;
	int corner_color;
	int corner_size;

	border_color = 0xFFFFFF;
	corner_color = 0xCCCCCC;
	corner_size = 3;
	
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

	// Углы
	i = 0;
	while (i < corner_size)
	{
		j = 0;
		while (j < corner_size)
		{
			put_pixel(&g->minimap, i, j, corner_color);
			put_pixel(&g->minimap, g->minimap.width - 1 - i, j, corner_color);
			put_pixel(&g->minimap, i, g->minimap.height - 1 - j, corner_color);
			put_pixel(&g->minimap, g->minimap.width - 1 - i, 
					  g->minimap.height - 1 - j, corner_color);
			j++;
		}
		i++;
	}
}


static void mlx_draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;

	while (1)
	{
		put_pixel(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

static void draw_fov(t_game *g)
{
	int     fov_length;
	int     fov_angle;
	int     minimap_scale;
	int     player_size;
	int     center_x;
	int     center_y;
	int     color;
	double  angle_start;
	double  angle_end;
	double  angle;
	int     x;
	int     y;
	int     length;

	fov_length = 20;
	fov_angle = 30;
	minimap_scale = 5;
	player_size = minimap_scale;
	center_x = (int)(g->pl.position_x * minimap_scale + 
					 (g->minimap.width - g->width * minimap_scale) / 2);
	center_y = (int)(g->pl.position_y * minimap_scale + 
					 (g->minimap.height - g->height * minimap_scale) / 2);
	color = 0x7F7F4C;

	angle_start = atan2(g->pl.dir_y, g->pl.dir_x) - (fov_angle * M_PI / 180.0);
	angle_end = atan2(g->pl.dir_y, g->pl.dir_x) + (fov_angle * M_PI / 180.0);

	angle = angle_start;
	while (angle <= angle_end)
	{
		x = center_x;
		y = center_y;
		length = 0;

		while (length < fov_length)
		{
			x = center_x + (int)(cos(angle) * length);
			y = center_y + (int)(sin(angle) * length);

			if (x < 0 || y < 0 || x >= g->minimap.width ||
				y >= g->minimap.height || g->map[y / minimap_scale][x / minimap_scale] == '1' ||
				g->map[y / minimap_scale][x / minimap_scale] == 'D')
			{
				break;
			}

			mlx_draw_line(&g->minimap, center_x + player_size / 2,
						  center_y + player_size / 2, x, y, color);
			length++;
		}
		angle += 0.01;
	}
}





void draw_minimap(t_game *g)
{
	int x;
	int y;
	int minimap_scale;
	int offset[2];
	int color;

	minimap_scale = 5;
	offset[0] = (g->minimap.width - g->width * minimap_scale) / 2;
	offset[1] = (g->minimap.height - g->height * minimap_scale) / 2;
	y = 0;
	while (y < g->height)
	{
		x = 0;
		while (x < g->width)
		{
			set_minimap_color(g, x, y, &color);
			draw_rect(&g->minimap, 
					  (t_vector){offset[0] + x * minimap_scale, offset[1] + y * minimap_scale},
					  (t_vector){minimap_scale, minimap_scale}, color, &g->win_img); // передаем фон
			x++;
		}
		y++;
	}
	draw_fov(g);

	draw_minimap_border(g);
}	

