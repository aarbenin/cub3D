/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:43:23 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/29 08:12:10 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

t_game	cub_init(void)
{
	t_game	g;

	g.rate = 30;
	g.nframes = 0;
	g.width = 0;            // Ширина окна, инициализируется нулём
	g.height = 0;           // Высота окна, инициализируется нулём
	g.fd = -1;              // Дескриптор файла, -1 означает,что файл ещё не открыт
	g.frame_count = 0;      // Счетчик кадров, инициализируется нулём
	g.pl.dir = 0;           // Направление игрока, инициализируется нулём
	g.map = NULL;           // Указатель на карту, инициализируется NULL (пусто)
	g.mlx_ptr = NULL;       // Указатель на MLX (MiniLibX),инициализируется NULL
	g.win_ptr = NULL;       // Указатель на окно, инициализируется NULL
	g.mlx_ptr = mlx_init(); // Инициализация MLX
	g.tex.floor = -1;       // Цвет пола, -1 указывает на неинициализированное значение
	g.tex.ceiling = -1;     // Цвет потолка, -1 указывает на неинициализированное значение
	g.pl.position_x = -1;   // Позиция игрока по X, -1 означает, что позиция не задана
	g.pl.position_y = -1;   // Позиция игрока по Y, -1 означает, что позиция не задана
	g.pl.speed = 0.10;      // Скорость игрока, инициализирована значением 0.10
	g.pl.door_cooldown = 0; // Охлаждение двери, инициализируется нулём
	g.rate = 30;            // Частота кадров или обновления, инициализируется значением 30
	init_sprites(&g);       // Инициализация спрайтов
							// Инициализация текстур дверей
	g.tex.door_closed = NULL;
	g.tex.door_open = NULL;
	ft_bzero(&g.pl.keys, sizeof(t_key)); // Обнуление структуры клавиш игрока
	return (g);                         
		// Возвращает инициализированную структуру игры
}

void	init_game(t_game *g, char *filename)
{
	*g = cub_init();
	read_map(filename, g);
}

void	init_minimap(t_game *g)
{
	g->minimap_scale = 5;
	g->minimap.width = g->width * g->minimap_scale;
	g->minimap.height = g->height * g->minimap_scale;
	g->minimap.i = mlx_new_image(g->mlx_ptr, g->minimap.width,
			g->minimap.height);
	if (!g->minimap.i)
	{
		printf("Error: Minimap image creation failed!\n");
		return ;
	}
	g->minimap.addr = mlx_get_data_addr(g->minimap.i, &g->minimap.bpp,
			&g->minimap.line_len, &g->minimap.endian);
}

void	init_attr(t_game *g)
{
	g->win_ptr = mlx_new_window(g->mlx_ptr, WIN_W, WIN_H, "Cub3D");
	g->win_img.i = mlx_new_image(g->mlx_ptr, WIN_W, WIN_H);
	g->win_img.addr = mlx_get_data_addr(g->win_img.i, &g->win_img.bpp,
			&g->win_img.line_len, &g->win_img.endian);
	printf("Main image initialized: width=%d, height=%d\n", WIN_W, WIN_H);
	printf("Map size before minimap init: width=%d, height=%d\n", g->width,
		g->height);
	init_minimap(g);
	printf("Minimap initialized: width=%d, height=%d\n", g->minimap.width,
		g->minimap.height);
	g->win_g.i = mlx_new_image(g->mlx_ptr, WIN_W, WIN_H);
	g->win_g.addr = mlx_get_data_addr(g->win_g.i, &g->win_g.bpp,
			&g->win_g.line_len, &g->win_g.endian);
	g->win_r.i = mlx_new_image(g->mlx_ptr, WIN_W, WIN_H);
	g->win_r.addr = mlx_get_data_addr(g->win_r.i, &g->win_r.bpp,
			&g->win_r.line_len, &g->win_r.endian);
	g->miniview.i = mlx_new_image(g->mlx_ptr, 30 * SIZE, 15 * SIZE);
	g->miniview.addr = mlx_get_data_addr(g->miniview.i, &g->miniview.bpp,
			&g->miniview.line_len, &g->miniview.endian);
	g->miniview.width = 30 * SIZE;
	g->miniview.height = 15 * SIZE;
	g->pl.speed = 0.02;
	printf("Final map size: width=%d, height=%d\n", g->width, g->height);
	printf("Final minimap size: width=%d, height=%d\n", g->minimap.width,
		g->minimap.height);
	printf("Final miniview size: width=%d, height=%d\n", g->miniview.width,
		g->miniview.height);
}

void	setup_game(t_game *g)
{
	init_attr(g);
	init_ray(g);
	//
	mlx_hook(g->win_ptr, 02, 1L << 0, cub_keydown, g);
	mlx_hook(g->win_ptr, 03, 1L << 1, cub_keyup, g);
	mlx_hook(g->win_ptr, 17, 0, cub_exit, g);
	mlx_hook(g->win_ptr, 6, 1L << 6, mouse_move, g);
	// Центрируем курсор, передавая и указатель на контекст MiniLibX
	mlx_mouse_move(g->mlx_ptr, g->win_ptr, WIN_W / 2, WIN_H / 2);
	mlx_loop_hook(g->mlx_ptr, cub_update, g);
	mlx_loop(g->mlx_ptr);
}

/**
 * Updates the textures for the game's animations.

	* This function cycles through the available textures for each wall direction (N,
	S, E, W),
 * allowing for animated wall textures in the game.
 *
 * @param g A pointer to the game state containing the textures.
 */

void	update_anim(t_game *g)
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