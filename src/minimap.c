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

//_________________minimap_border.c_____________________
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
		e2 = b.err << 1; //вместо умножения на 2, пытаюсь экономить ресурсы
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

static void	set_minimap_color(t_game *g, int x, int y, int *color)
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
