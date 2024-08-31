/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:54:21 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/19 11:26:44 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CAST_H
# define RAY_CAST_H

# include "cub3D.h"

/* Структура для хранения данных по лучам */
typedef struct s_ray
{
	float angle_increment; // Угол между лучами
	float current_angle;   // Текущий угол луча
	float cos;			   // Косинус угла луча
	float sin;			   // Синус угла луча
	float hfov;			   // Горизонтальное поле зрения
	float max_distance;	   // Предел расстояния для лучей
	int precision;		   // Точность расчета лучей
} t_ray;

typedef struct s_ray_data
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
} t_ray_data;

#endif