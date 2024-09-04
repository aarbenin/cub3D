#include "../inc/cub3D.h"

//_______________________draw_background.c___________________________

// void	draw_background(t_game *g)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	// Отрисовка потолка
// 	while (y < WIN_H / 2)
// 	{
// 		x = 0;
// 		while (x < WIN_W)
// 		{
// 			put_pixel(&g->win_img, x, y, g->tex.ceiling);
// 			x++;
// 		}
// 		y++;
// 	}
// 	// Отрисовка пола
// 	while (y < WIN_H)
// 	{
// 		x = 0;
// 		while (x < WIN_W)
// 		{
// 			put_pixel(&g->win_img, x, y, g->tex.floor);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// with gradient
static void	fill_background(t_img *img, int color, int start_y, int end_y)
{
	int	x;
	int	y;

	y = start_y;
	while (y < end_y)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

static int	adjust_brightness(int color, int factor)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * factor / 255;
	g = ((color >> 8) & 0xFF) * factor / 255;
	b = (color & 0xFF) * factor / 255;
	return ((r << 16) | (g << 8) | b);
}


static int	calculate_gradient(int base_color, int y, int height, int is_ceiling)
{
	double	distance_factor;

	if (is_ceiling)
		distance_factor = 0.5 + 0.5 * (1.0 - ((double)y / (height / 2)));
	else
		distance_factor = 0.5 + 0.5 * (((double)(y - height / 2)) / (height / 2));
	return (adjust_brightness(base_color, (int)(distance_factor * 255)));
}

void	draw_background(t_game *g)
{
	int	ceiling_color;
	int	floor_color;
	int	y;

	y = 0;
	while (y < WIN_H / 2)
	{
		ceiling_color = calculate_gradient(g->tex.ceiling, y, WIN_H, 1);
		fill_background(&g->win_img, ceiling_color, y, y + 1);
		y++;
	}
	while (y < WIN_H)
	{
		floor_color = calculate_gradient(g->tex.floor, y, WIN_H, 0);
		fill_background(&g->win_img, floor_color, y, y + 1);
		y++;
	}
}

