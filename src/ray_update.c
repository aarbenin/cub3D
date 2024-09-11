#include "../inc/cub3D.h"

static inline void	update_ray_pos(t_ray_data *ray, double delta_x,
		double delta_y)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += delta_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += delta_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}
static inline bool	check_hit(t_game *g, t_ray_data *ray)
{
	char	cell;

	cell = g->map[ray->map_y][ray->map_x];
	return (cell == '1' || cell == 'D');
}

void	perform_dda(t_game *g, t_ray_data *ray, double delta_x, double delta_y)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		update_ray_pos(ray, delta_x, delta_y);
		hit = check_hit(g, ray);
	}
}
