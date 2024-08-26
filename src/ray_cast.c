/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:29:11 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/26 13:11:27 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

//________________________movement.c________________________
static void	set_direction_north(t_player *pl)
{
	pl->dir_x = 0;
	pl->dir_y = -1;
	pl->plane_x = 0.66;
	pl->plane_y = 0;
}

static void	set_direction_south(t_player *pl)
{
	pl->dir_x = 0;
	pl->dir_y = 1;
	pl->plane_x = -0.66;
	pl->plane_y = 0;
}

static void	set_direction_east(t_player *pl)
{
	pl->dir_x = 1;
	pl->dir_y = 0;
	pl->plane_x = 0;
	pl->plane_y = 0.66;
}

static void	set_direction_west(t_player *pl)
{
	pl->dir_x = -1;
	pl->dir_y = 0;
	pl->plane_x = 0;
	pl->plane_y = -0.66;
}

static void	set_player_direction(t_player *pl, char dir)
{
	if (dir == 'N')
		set_direction_north(pl);
	else if (dir == 'S')
		set_direction_south(pl);
	else if (dir == 'E')
		set_direction_east(pl);
	else if (dir == 'W')
		set_direction_west(pl);
}

//_______________________ray.c_________________________________________

static void	set_ray_params(t_ray *ray)
{
	ray->hfov = 30;
	ray->angle_increment = 2 * ray->hfov / WIN_W;
	ray->precision = 50;
	ray->max_distance = 10;
}

void	init_ray(t_text_game *g)
{
	set_player_direction(&g->pl, g->pl.dir);
	set_ray_params(&g->ray);
	printf("Initial Direction: dir_x = %f, dir_y = %f\n",
		g->pl.dir_x, g->pl.dir_y);
	printf("Initial Plane: plane_x = %f, plane_y = %f\n",
		g->pl.plane_x, g->pl.plane_y);
}


static void	init_ray_data(t_text_game *g, t_ray_data *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_W - 1;
	ray->ray_dir_x = g->pl.dir_x + g->pl.plane_x * camera_x;
	ray->ray_dir_y = g->pl.dir_y + g->pl.plane_y * camera_x;
	ray->map_x = (int)g->pl.position_x;
	ray->map_y = (int)g->pl.position_y;
}

//____________________________raycast______________________________

static void calculate_step_and_side_dist(t_text_game *g, t_ray_data *ray)
{
	double delta_dist_x;
	double delta_dist_y;
	
	delta_dist_x = fabs(1 / ray->ray_dir_x);
	delta_dist_y = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (g->pl.position_x - ray->map_x) * delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - g->pl.position_x) * delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (g->pl.position_y - ray->map_y) * delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - g->pl.position_y) * delta_dist_y;
	}
}


static void perform_dda(t_text_game *g, t_ray_data *ray)
{
	double delta_dist_x = fabs(1 / ray->ray_dir_x);
	double delta_dist_y = fabs(1 / ray->ray_dir_y);
	int hit = 0;
	
	delta_dist_x = fabs(1 / ray->ray_dir_x);
	delta_dist_y = fabs(1 / ray->ray_dir_y);
	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (g->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

static void	calculate_perp_wall_dist(t_text_game *g, t_ray_data *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - g->pl.position_x 
			+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - g->pl.position_y 
			+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
}


//____________________________draw_texture.c_____________________________________
// Вычисляет координату X на текстуре в зависимости от направления луча и стороны стены
static int	calculate_tex_x(t_texture_params *tex_params)
{
	int	tex_x;

	tex_x = (int)(tex_params->params->wall_x * (float)tex_params->texture->width);
	if ((tex_params->ray->side == 0 && tex_params->ray->ray_dir_x > 0) ||
		(tex_params->ray->side == 1 && tex_params->ray->ray_dir_y < 0))
		tex_x = tex_params->texture->width - tex_x - 1;
	return (tex_x);
}

// Отрисовывает вертикальную линию текстуры на экране
static void	draw_vertical_texture_line(t_text_game *g, int x,
					t_texture_params *tex_params, int tex_x)
{
	int		y;
	int		tex_y;
	int		color;
	float	step;
	float	tex_pos;

	// Определяет шаг текстуры и начальную позицию на текстуре
	step = 1.0 * tex_params->texture->height / tex_params->params->line_height;
	tex_pos = (tex_params->params->draw_start - WIN_H / 2 +
		tex_params->params->line_height / 2) * step;
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

void	draw_texture_line(t_text_game *g, int x, t_img *texture,
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

//________________________draw_wall.c________________________

// Вычисляет высоту линии и границы рисования на экране
static void	calculate_line_height(t_ray_data *ray, t_wall_params *wall_params)
{
	wall_params->params.line_height = (int)(WIN_H / ray->perp_wall_dist);
	wall_params->params.draw_start = -wall_params->params.line_height / 2 + WIN_H / 2;
	if (wall_params->params.draw_start < 0)
		wall_params->params.draw_start = 0;
	wall_params->params.draw_end = wall_params->params.line_height / 2 + WIN_H / 2;
	if (wall_params->params.draw_end >= WIN_H)
		wall_params->params.draw_end = WIN_H - 1;
}

// Определяет текстуру в зависимости от направления удара луча
static t_img	*select_texture(t_text_game *g, t_ray_data *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return ((t_img *)g->tex.e->content); // Восточная стена
		else
			return ((t_img *)g->tex.w->content); // Западная стена
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return ((t_img *)g->tex.s->content); // Южная стена
		else
			return ((t_img *)g->tex.n->content); // Северная стена
	}
}

// Вычисляет точную координату пересечения стены в текстуре
static void	calculate_wall_hit_x(t_text_game *g, t_ray_data *ray, t_wall_params *wall_params)
{
	if (ray->side == 0)
		wall_params->wall_x = g->pl.position_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_params->wall_x = g->pl.position_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_params->wall_x -= floor(wall_params->wall_x); // Убираем целую часть
}

void	draw_wall_line(t_text_game *g, int x, t_ray_data *ray)
{
	t_wall_params	wall_params;

	calculate_line_height(ray, &wall_params);
	wall_params.texture = select_texture(g, ray);
	calculate_wall_hit_x(g, ray, &wall_params);
	// Установка параметров рисования
	wall_params.params.wall_x = wall_params.wall_x;
	draw_texture_line(g, x, wall_params.texture, &wall_params.params, ray);
}

//_____________________ray_cast.c__________________________________________


static void cast_single_ray(t_text_game *g, t_ray_data *ray, int x)
{
	init_ray_data(g, ray, x);
	calculate_step_and_side_dist(g, ray);
	perform_dda(g, ray);
	calculate_perp_wall_dist(g, ray);
	draw_wall_line(g, x, ray);
}

void cast_rays_recursive(t_text_game *g, int x)
{
	t_ray_data ray;

	if (x >= WIN_W)
		return ;
	cast_single_ray(g, &ray, x);
	cast_rays_recursive(g, x + 1);
}

void cast_rays(t_text_game *g)
{
	cast_rays_recursive(g, 0);
}

//_______________________scene.c_______________________________
void	draw_background(t_text_game *g)
{
	int x, y;
	y = 0;
	// Отрисовка потолка
	while (y < WIN_H / 2)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(&g->win_img, x, y, g->tex.ceiling);
			x++;
		}
		y++;
	}
	// Отрисовка пола
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(&g->win_img, x, y, g->tex.floor);
			x++;
		}
		y++;
	}
}