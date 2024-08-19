/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 08:54:21 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/14 08:56:39 by ogoman           ###   ########.fr       */
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

#endif