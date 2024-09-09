
#include "../inc/cub3D.h"

static inline void	calculate_ray_steps(t_game *g, t_ray_data *ray,
		double delta_dist_x, double delta_dist_y)
{
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

static inline void	calculate_wall_dist(t_game *g, t_ray_data *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - g->pl.position_x + (1 - ray->step_x)
				/ 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - g->pl.position_y + (1 - ray->step_y)
				/ 2) / ray->ray_dir_y;
}

static inline void	calculate_delta_dist(t_ray_data *ray, double *delta_dist_x,
		double *delta_dist_y)
{
	*delta_dist_x = 1.0 / (fabs(ray->ray_dir_x) + 1e-9);
	*delta_dist_y = 1.0 / (fabs(ray->ray_dir_y) + 1e-9);
}

void	cast_rays(t_game *g)
{
	t_ray_data	ray;
	int			x;
	double		camera_x;
	double		delta_dist_x;
	double		delta_dist_y;

	x = 0;
	while (x < WIN_W)
	{
		camera_x = 2 * x / (double)WIN_W - 1;
		ray.ray_dir_x = g->pl.dir_x + g->pl.plane_x * camera_x;
		ray.ray_dir_y = g->pl.dir_y + g->pl.plane_y * camera_x;
		ray.map_x = (int)g->pl.position_x;
		ray.map_y = (int)g->pl.position_y;
		calculate_delta_dist(&ray, &delta_dist_x, &delta_dist_y);
		calculate_ray_steps(g, &ray, delta_dist_x, delta_dist_y);
		perform_dda(g, &ray, delta_dist_x, delta_dist_y);
		calculate_wall_dist(g, &ray);
		draw_wall_line(g, x, &ray);
		x++;
	}
}
