
#include "../inc/cub3D.h"

static void	set_ray_params(t_ray *ray)
{
	ray->hfov = 30;
	ray->angle_increment = 2 * ray->hfov / WIN_W;
	ray->precision = 50;
	ray->max_distance = 10;
}

void	init_ray(t_game *g)
{
	set_player_direction(&g->pl, g->pl.dir);
	set_ray_params(&g->ray);
	printf("Initial Direction: dir_x = %f, dir_y = %f\n", g->pl.dir_x,
		g->pl.dir_y);
	printf("Initial Plane: plane_x = %f, plane_y = %f\n", g->pl.plane_x,
		g->pl.plane_y);
}

// static void	init_ray_data(t_game *g, t_ray_data *ray, int x)
// {
// 	double	camera_x;

// 	camera_x = 2 * x / (double)WIN_W - 1;
// 	ray->ray_dir_x = g->pl.dir_x + g->pl.plane_x * camera_x;
// 	ray->ray_dir_y = g->pl.dir_y + g->pl.plane_y * camera_x;
// 	ray->map_x = (int)g->pl.position_x;
// 	ray->map_y = (int)g->pl.position_y;
// }

//____________________________raycast______________________________

static void	calculate_step_and_side_dist(t_game *g, t_ray_data *ray,
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

static void	update_ray(t_ray_data *ray, double delta_x, double delta_y)
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

static inline int	check_hit(t_game *g, t_ray_data *ray)
{
	char	cell;

	cell = g->map[ray->map_y][ray->map_x];
	return (cell == '1' || cell == 'D' || cell == 'O');
}

static void	perform_dda(t_game *g, t_ray_data *ray)
{
	double	delta_x;
	double	delta_y;

	delta_x = fabs(1 / ray->ray_dir_x);
	delta_y = fabs(1 / ray->ray_dir_y);
	while (!check_hit(g, ray))
	{
		update_ray(ray, delta_x, delta_y);
	}
}

static void	calculate_perp_wall_dist(t_game *g, t_ray_data *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - g->pl.position_x + (1 - ray->step_x)
				/ 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - g->pl.position_y + (1 - ray->step_y)
				/ 2) / ray->ray_dir_y;
}

static void	calculate_delta_dist(t_ray_data *ray, double *delta_dist_x,
		double *delta_dist_y)
{
	if (ray->ray_dir_x == 0)
		*delta_dist_x = 1e30;
	else
		*delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		*delta_dist_y = 1e30;
	else
		*delta_dist_y = fabs(1 / ray->ray_dir_y);
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
		calculate_step_and_side_dist(g, &ray, delta_dist_x, delta_dist_y);
		perform_dda(g, &ray);
		calculate_perp_wall_dist(g, &ray);
		draw_wall_line(g, x, &ray);
		x++;
	}
}
