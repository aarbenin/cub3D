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
	init_welcome_screen(&g);
	return (g);                         
		// Возвращает инициализированную структуру игры
}

void	init_welcome_screen(t_game *g)
{
	g->welcome_screen = load_img(g->mlx_ptr, "./textures/welcome_scr.xpm");
	if (!g->welcome_screen)
		handle_error(ERR_INV_PATH, g, NULL, 1);
	g->scaled_welcome.i = NULL;
	g->is_paused = 1;
	g->was_paused = 0;
	printf("debug: Welcome screen initialized: width = %d, height = %d\n",
		g->welcome_screen->width, g->welcome_screen->height);
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
	g->window_width = WIN_W;
	g->window_height = WIN_H;
	g->win_ptr = mlx_new_window(g->mlx_ptr, g->window_width, g->window_height,
			"Cub3D");
	g->win_img.i = mlx_new_image(g->mlx_ptr, g->window_width, g->window_height);
	g->win_img.addr = mlx_get_data_addr(g->win_img.i, &g->win_img.bpp,
			&g->win_img.line_len, &g->win_img.endian);

	printf("debug: Main image initialized: width=%d, height=%d\n",
		g->window_width, g->window_height);
	init_minimap(g);
	printf("debug: Minimap initialized: width=%d, height=%d\n",
		g->minimap.width, g->minimap.height);
	g->miniview.i = mlx_new_image(g->mlx_ptr, 30 * SIZE, 15 * SIZE);
	g->miniview.addr = mlx_get_data_addr(g->miniview.i, &g->miniview.bpp,
			&g->miniview.line_len, &g->miniview.endian);
	g->miniview.width = 30 * SIZE;
	g->miniview.height = 15 * SIZE;
	g->pl.speed = 0.02;
	printf("debug: Final minimap size: width=%d, height=%d\n", g->minimap.width,
		g->minimap.height);
	printf("debug: Final miniview size: width=%d, height=%d\n",
		g->miniview.width, g->miniview.height);
}


void	setup_game(t_game *g)
{
	init_attr(g);
	init_ray(g);

	mlx_hook(g->win_ptr, 02, 1L << 0, cub_keydown, g);
	mlx_hook(g->win_ptr, 03, 1L << 1, cub_keyup, g);
	mlx_hook(g->win_ptr, 17, 0, cub_exit, g);
	mlx_hook(g->win_ptr, 6, 1L << 6, mouse_move, g);
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
