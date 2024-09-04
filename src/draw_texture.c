#include "../inc/cub3D.h"


// Вычисляет координату X на текстуре в зависимости от направления луча и стороны стены
static int	calculate_tex_x(t_texture_params *tex_params)
{
	int	tex_x;

	tex_x = (int)(tex_params->params->wall_x
			* (float)tex_params->texture->width);
	if ((tex_params->ray->side == 0 && tex_params->ray->ray_dir_x > 0)
		|| (tex_params->ray->side == 1 && tex_params->ray->ray_dir_y < 0))
		tex_x = tex_params->texture->width - tex_x - 1;
	return (tex_x);
}

// Отрисовывает вертикальную линию текстуры на экране
static void	draw_vertical_texture_line(t_game *g, int x,
		t_texture_params *tex_params, int tex_x)
{
	int		y;
	int		tex_y;
	int		color;
	float	step;
	float	tex_pos;

	// Определяет шаг текстуры и начальную позицию на текстуре
	step = 1.0 * tex_params->texture->height / tex_params->params->line_height;
	tex_pos = (tex_params->params->draw_start - WIN_H / 2
			+ tex_params->params->line_height / 2) * step;
	y = tex_params->params->draw_start;
	while (y < tex_params->params->draw_end)
	{
		tex_y = (int)tex_pos & (tex_params->texture->height - 1);
		tex_pos += step;
		color = get_pixel_color(tex_params->texture, tex_x, tex_y);
		// Затемняет пиксель, если это боковая стена
		if (tex_params->ray->side == 1)
			color = (color >> 1) & 0x7F7F7F;
		put_pixel(&g->win_img, x, y, color);
		y++;
	}
}

void	draw_texture_line(t_game *g, int x, t_img *texture,
		t_draw_params *params, t_ray_data *ray)
{
	int					tex_x;
	t_texture_params	tex_params;

	tex_params.texture = texture;
	tex_params.params = params;
	tex_params.ray = ray;
	tex_x = calculate_tex_x(&tex_params);
	draw_vertical_texture_line(g, x, &tex_params, tex_x);
}