/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:29:11 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/26 08:35:47 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * Initializes raycasting parameters based on the player's direction.
 *
 * @param g A pointer to a t_text_game structure that contains game state information.
 *
 * This function sets up the initial parameters for raycasting in the game.
 * It determines the current angle of the ray based on the player's direction
 * and sets other raycasting-related parameters such as the horizontal field of view
 * (hfov), angle increment per pixel, precision, and maximum distance for raycasting.
 */
void init_ray(t_text_game *g)
{
    if (g->pl.dir == 'N')
    {
        g->pl.dir_x = 0;
        g->pl.dir_y = -1;
        g->pl.plane_x = 0.66;
        g->pl.plane_y = 0;
    }
    else if (g->pl.dir == 'S')
    {
        g->pl.dir_x = 0;
        g->pl.dir_y = 1;
        g->pl.plane_x = -0.66;
        g->pl.plane_y = 0;
    }
    else if (g->pl.dir == 'E')
    {
        g->pl.dir_x = 1;
        g->pl.dir_y = 0;
        g->pl.plane_x = 0;
        g->pl.plane_y = 0.66;
    }
    else if (g->pl.dir == 'W')
    {
        g->pl.dir_x = -1;
        g->pl.dir_y = 0;
        g->pl.plane_x = 0;
        g->pl.plane_y = -0.66;
    }
    g->ray.hfov = 30;
    g->ray.angle_increment = 2 * g->ray.hfov / WIN_W;
    g->ray.precision = 50;
    g->ray.max_distance = 10;

    printf("Initial Direction: dir_x = %f, dir_y = %f\n", g->pl.dir_x, g->pl.dir_y);
    printf("Initial Plane: plane_x = %f, plane_y = %f\n", g->pl.plane_x, g->pl.plane_y);
}


// void draw_vertical_line(t_text_game *g, int x, int draw_start, int draw_end, int color)
// {
//     if (draw_start > draw_end || draw_start >= WIN_H || draw_end < 0)
//         return ;
//     put_pixel(&g->win_img, x, draw_start, color);
//     draw_vertical_line(g, x, draw_start + 1, draw_end, color);
// }


static void init_ray_data(t_text_game *g, t_ray_data *ray, int x)
{
    double ray_angle;

    ray_angle = g->ray.current_angle - g->ray.hfov + x * g->ray.angle_increment;
    ray->ray_dir_x = cos(ray_angle * M_PI / 180);
    ray->ray_dir_y = sin(ray_angle * M_PI / 180);

    ray->map_x = (int)g->pl.position_x;
    ray->map_y = (int)g->pl.position_y;
}

static void calculate_step_and_side_dist(t_text_game *g, t_ray_data *ray)
{
    double delta_dist_x = fabs(1 / ray->ray_dir_x);
    double delta_dist_y = fabs(1 / ray->ray_dir_y);

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

static void calculate_perp_wall_dist(t_text_game *g, t_ray_data *ray)
{
    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map_x - g->pl.position_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->perp_wall_dist = (ray->map_y - g->pl.position_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

// static void draw_wall_line(t_text_game *g, int x, t_ray_data *ray)
// {
//     int line_height;
//     int draw_start;
//     int draw_end;
//     int color;

//     line_height = (int)(WIN_H / ray->perp_wall_dist);
//     draw_start = -line_height / 2 + WIN_H / 2;
//     if (draw_start < 0)
//         draw_start = 0;
//     draw_end = line_height / 2 + WIN_H / 2;
//     if (draw_end >= WIN_H)
//         draw_end = WIN_H - 1;

//     color = 0xFFFFFF;
//     if (ray->side == 1)
//         color /= 2;
//     draw_vertical_line(g, x, draw_start, draw_end, color);
// }

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