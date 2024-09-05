#include "../inc/cub3D.h"

static void	fill_row(t_img *img, int color, int y)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		put_pixel(img, x, y, color);
		x++;
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

static int	calculate_gradient(int base_color, int y, int height,
		int is_ceiling)
{
	double	distance_factor;

	if (is_ceiling)
		distance_factor = 0.5 + 0.5 * (1.0 - ((double)y / (height / 2)));
	else
		distance_factor = 0.5 + 0.5 * (((double)(y - height / 2)) / (height
					/ 2));
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
		fill_row(&g->win_img, ceiling_color, y);
		y++;
	}
	while (y < WIN_H)
	{
		floor_color = calculate_gradient(g->tex.floor, y, WIN_H, 0);
		fill_row(&g->win_img, floor_color, y);
		y++;
	}
}
