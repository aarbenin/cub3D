#include "../inc/cub3D.h"

static void	calculate_line_height(t_ray_data *ray, t_wall_params *wall_params)
{
	wall_params->params.line_height = (int)(WIN_H / ray->perp_wall_dist);
	wall_params->params.draw_start = -wall_params->params.line_height / 2
		+ WIN_H / 2;
	if (wall_params->params.draw_start < 0)
		wall_params->params.draw_start = 0;
	wall_params->params.draw_end = wall_params->params.line_height / 2 + WIN_H
		/ 2;
	if (wall_params->params.draw_end >= WIN_H)
		wall_params->params.draw_end = WIN_H - 1;
}

static t_img	*select_texture(t_game *g, t_ray_data *ray)
{
	char	cell;

	cell = g->map[ray->map_y][ray->map_x];
	if (cell == 'D')
		return (g->tex.door_closed);
	else if (cell == 'O')
		return (g->tex.door_open);
	else if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return ((t_img *)g->tex.e->content);
		else
			return ((t_img *)g->tex.w->content);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return ((t_img *)g->tex.s->content);
		else
			return ((t_img *)g->tex.n->content);
	}
}

static void	calculate_wall_hit_x(t_game *g, t_ray_data *ray,
		t_wall_params *wall_params)
{
	if (ray->side == 0)
		wall_params->wall_x = g->pl.position_y + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		wall_params->wall_x = g->pl.position_x + ray->perp_wall_dist
			* ray->ray_dir_x;
	wall_params->wall_x -= floor(wall_params->wall_x);
}

void	draw_wall_line(t_game *g, int x, t_ray_data *ray)
{
	t_wall_params	wall_params;

	calculate_line_height(ray, &wall_params);
	wall_params.texture = select_texture(g, ray);
	calculate_wall_hit_x(g, ray, &wall_params);
	wall_params.params.wall_x = wall_params.wall_x;
	draw_texture_line(g, x, wall_params.texture, &wall_params.params, ray);
}
