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
