/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:43:23 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/26 13:39:27 by aarbenin         ###   ########.fr       */
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
    if (k == KEY_LEFT) // Обработка отпускания стрелки влево
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



