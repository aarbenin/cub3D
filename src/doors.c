#include "../inc/cub3D.h"



/**
 * Handles the player's interaction with doors in the game.
 * If the player is near a door and presses the interaction key,
 * this function will either open or close the door, depending on its current state.
 *
 * @param g A pointer to the game state containing the player, map, and other game data.
 */

void action_door(t_game *g)
{
	float d;       // Расстояние до двери
	float pos_x;   // Координата X
	float pos_y;   // Координата Y
	float x;       // Временная переменная для расчета
	float y;       // Временная переменная для расчета

	// Получаем текущие координаты игрока
	pos_x = g->pl.position_x;
	pos_y = g->pl.position_y;

	// Проверяем, есть ли возможность взаимодействия с дверью
	if (g->pl.door_cooldown || ft_strchr("oc", g->map[(int)(pos_y + 0.5)][(int)(pos_x + 0.5)]))
		return;

	// Вычисляем расстояние до двери и получаем координаты
	d = distance_to_door(g, g->ray.current_angle, &x, &y);

	// Обрабатываем открытие двери
	if (d < g->ray.max_distance && g->map[(int)pos_y][(int)pos_x] == 'c')
	{
		g->pl.door_cooldown = 1;
		g->map[(int)pos_y][(int)pos_x] = 'o';
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->win_g.i, 0, 0);
	}
	// Обрабатываем закрытие двери
	else if (d < g->ray.max_distance && g->map[(int)pos_y][(int)pos_x] == 'o')
	{
		g->pl.door_cooldown = 1;
		g->map[(int)pos_y][(int)pos_x] = 'c';
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->win_r.i, 0, 0);
	}
}

/**
 * Calculates the distance from the player to the nearest door along the given ray angle.
 * This function uses raycasting principles to detect the nearest door
 * in the direction the player is facing.
 *
 * @param g A pointer to the game state containing the player, map, and raycasting data.
 * @param ray_angle The angle at which the ray is cast to detect the door.
 * @param pos_x A pointer to store the X coordinate of the detected door.
 * @param pos_y A pointer to store the Y coordinate of the detected door.
 * @return The distance from the player to the nearest door.
 */

float distance_to_door(t_game *g, float ray_angle, float *pos_x, float *pos_y)
{
	float d;             // Расстояние до двери
	float ray_cos;       // Косинус угла луча
	float ray_sin;       // Синус угла луча

	// Вычисляем косинус и синус угла луча с учетом точности
	ray_cos = cos(degree_to_radians(ray_angle)) / g->ray.precision;
	ray_sin = sin(degree_to_radians(ray_angle)) / g->ray.precision;

	// Начальные координаты для поиска двери
	*pos_x = g->pl.position_x + 0.5;
	*pos_y = g->pl.position_y + 0.5;

	// Цикл поиска двери на карте
	while (!ft_strchr("1oc", g->map[(int)*pos_y][(int)*pos_x]) && \
		   sqrt(powf(*pos_x - g->pl.position_x - 0.5, 2.) + \
		   powf(*pos_y - g->pl.position_y - 0.5, 2.)) < g->ray.max_distance)
	{
		*pos_x += ray_cos;
		*pos_y += ray_sin;
	}

	// Вычисление расстояния до двери
	d = sqrt(powf(*pos_x - g->pl.position_x - 0.5, 2.) + \
			 powf(*pos_y - g->pl.position_y - 0.5, 2.));

	// Коррекция расстояния с учетом угла луча
	d *= cos(degree_to_radians(ray_angle - g->ray.current_angle));
	return d;
}

/**
 * Converts an angle from degrees to radians.
 * This is necessary for trigonometric calculations,
 * as most math functions in C use radians.
 *
 * @param degree The angle in degrees.
 * @return The equivalent angle in radians.
 */

float	degree_to_radians(float degree)
{
	return (degree * M_PI / 180);
}
