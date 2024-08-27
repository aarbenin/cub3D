/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:43:23 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/27 10:56:11 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * Handles key release events. Updates the game state based on the key released.
 * 
 * @param key The key that was released.
 * @param g A pointer to the game state.
 * @return Always returns 0.
 */
int cub_keydown(int k, t_text_game *g)
{
    if (k == KEY_Q || k == KEY_ESC)
        handle_error(ERR_END, g, NULL, 1);
    else if (k == KEY_LEFT) // Обработка нажатия стрелки влево
        g->pl.keys.left_pressed = 1;
    else if (k == KEY_RIGHT) // Обработка нажатия стрелки вправо
        g->pl.keys.right_pressed = 1;
    else if (k == KEY_W)
        g->pl.keys.w_pressed = 1;
    else if (k == KEY_A)
        g->pl.keys.a_pressed = 1;
    else if (k == KEY_S)
        g->pl.keys.s_pressed = 1;
    else if (k == KEY_D)
        g->pl.keys.d_pressed = 1;

    return (0);
}

int cub_keyup(int k, t_text_game *g)
{
    if (k == KEY_E)
		action_door(g);
    else if (k == KEY_LEFT) // Обработка отпускания стрелки влево
        g->pl.keys.left_pressed = 0;
    else if (k == KEY_RIGHT) // Обработка отпускания стрелки вправо
        g->pl.keys.right_pressed = 0;
    else if (k == KEY_W)
        g->pl.keys.w_pressed = 0;
    else if (k == KEY_A)
        g->pl.keys.a_pressed = 0;
    else if (k == KEY_S)
        g->pl.keys.s_pressed = 0;
    else if (k == KEY_D)
        g->pl.keys.d_pressed = 0;

    return (0);
}

/**
 * Initializes attributes for the game window and images.
 * 
 * @param g A pointer to the game state.
 */
void init_attr(t_text_game *g)
{
	g->win_ptr = mlx_new_window(g->mlx_ptr, WIN_W, WIN_H, "Cub3D");
	g->win_img.i = mlx_new_image(g->mlx_ptr, WIN_W, WIN_H);
	g->win_img.addr = mlx_get_data_addr(g->win_img.i, &g->win_img.bpp,
										&g->win_img.line_len, &g->win_img.endian);
	g->minimap.i = mlx_new_image(g->mlx_ptr, g->width * SIZE,
								 g->height * SIZE);
    g->win_g.i = mlx_new_image(g->mlx_ptr, WIN_W, WIN_H);
    g->win_g.addr = mlx_get_data_addr(g->win_g.i, &g->win_g.bpp,
		&g->win_g.line_len, &g->win_g.endian);
    g->win_r.i = mlx_new_image(g->mlx_ptr, WIN_W, WIN_H);
	g->win_r.addr = mlx_get_data_addr(g->win_r.i, &g->win_r.bpp,
		&g->win_r.line_len, &g->win_r.endian);
	g->minimap.addr = mlx_get_data_addr(g->minimap.i, &g->minimap.bpp,
										&g->minimap.line_len, &g->minimap.endian);
	g->miniview.i = mlx_new_image(g->mlx_ptr, 30 * SIZE, 15 * SIZE);
	g->miniview.addr = mlx_get_data_addr(g->miniview.i, &g->miniview.bpp,
										 &g->miniview.line_len, &g->miniview.endian);
	g->miniview.width = 30 * SIZE;
	g->miniview.height = 15 * SIZE;
	g->pl.speed = 0.02;  

}

/**
 * Initializes the game by setting up attributes, raycasting, and event hooks.
 * 
 * @param g A pointer to the game state.
 */
void	game_init(t_text_game *g)
{
	init_attr(g);
	init_ray(g);

	// Настраиваем обработку клавиш
	mlx_hook(g->win_ptr, 02, 1L << 0, cub_keydown, g);
	mlx_hook(g->win_ptr, 03, 1L << 1, cub_keyup, g);
	mlx_hook(g->win_ptr, 17, 0, cub_exit, g);

	// Добавляем обработку движения мыши
	mlx_hook(g->win_ptr, 6, 1L << 6, mouse_move, g);

	// Центрируем курсор, передавая и указатель на контекст MiniLibX
	mlx_mouse_move(g->mlx_ptr, g->win_ptr, WIN_W / 2, WIN_H / 2);

	mlx_loop_hook(g->mlx_ptr, cub_update, g);
	mlx_loop(g->mlx_ptr);
}


/**
 * Handles the player's interaction with doors in the game.
 * If the player is near a door and presses the interaction key,
 * this function will either open or close the door, depending on its current state.
 *
 * @param g A pointer to the game state containing the player, map, and other game data.
 */

void action_door(t_text_game *g)
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

float distance_to_door(t_text_game *g, float ray_angle, float *pos_x, float *pos_y)
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

/**
 * Updates the textures for the game's animations.
 * This function cycles through the available textures for each wall direction (N, S, E, W),
 * allowing for animated wall textures in the game.
 *
 * @param g A pointer to the game state containing the textures.
 */

void	update_anim(t_text_game *g)
{
	g->tex.n = g->tex.n->next;
	if (!g->tex.n)
		g->tex.n = g->tex.n_bak;
	g->tex.s = g->tex.s->next;
	if (!g->tex.s)
		g->tex.s = g->tex.s_bak;
	g->tex.e = g->tex.e->next;
	if (!g->tex.e)
		g->tex.e = g->tex.e_bak;
	g->tex.w = g->tex.w->next;
	if (!g->tex.w)
		g->tex.w = g->tex.w_bak;
}