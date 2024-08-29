#include "../inc/cub3D.h"

static void draw_rect(t_img *img, t_vector position, t_vector dimensions, int color)
{
	int x;
	int y;

	y = 0;
	while (y < dimensions.y)
	{
		x = 0;
		while (x < dimensions.x)
		{
			put_pixel(img, position.x + x, position.y + y, color);
			x++;
		}
		y++;
	}
};

static void	set_minimap_color(t_game *g, int x, int y, int *color)
{
	if (g->map[y][x] == '1')
		*color = 0xFFFFFF; // Белый для стен
	else if (y == (int)g->pl.position_y && x == (int)g->pl.position_x)
		*color = 0x00FF00; // Зеленый для игрока
	else
		*color = 0x000000; // Чёрный для пустых клеток
}


void	draw_minimap(t_game *g)
{
	int	x;
	int	y;
	int	minimap_scale;
	int	offset[2];
	int	color;

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
			draw_rect(&g->minimap, (t_vector){offset[0] + x * minimap_scale,
				offset[1] + y * minimap_scale},
				(t_vector){minimap_scale, minimap_scale}, color);
			x++;
		}
		y++;
	}
}
