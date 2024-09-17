/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:43:23 by ogoman            #+#    #+#             */
/*   Updated: 2024/09/17 06:37:09 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief Initializes the game structure with default values and resources.
 *
 * @return A fully initialized t_game structure.
 */
t_game	cub_init(void)
{
	t_game	g;

	g.rate = 30;
	g.nframes = 0;
	g.width = 0;
	g.height = 0;
	g.fd = -1;
	g.frame_count = 0;
	g.pl.dir = 0;
	g.map = NULL;
	g.mlx_ptr = NULL;
	g.win_ptr = NULL;
	g.mlx_ptr = mlx_init();
	g.tex.floor = -1;
	g.tex.ceiling = -1;
	g.pl.position_x = -1;
	g.pl.position_y = -1;
	g.pl.speed = 0.10;
	g.rate = 30;
	init_sprites(&g);
	g.tex.door_closed = NULL;
	g.tex.door_open = NULL;
	ft_bzero(&g.pl.keys, sizeof(t_key));
	init_welcome_screen(&g);
	return (g);
}

/**
 * @brief Loads and initializes the welcome screen image.
 *
 * @param g Pointer to the game structure.
 */
void	init_welcome_screen(t_game *g)
{
	g->welcome_screen = load_img(g->mlx_ptr, "./textures/welcome_scr.xpm");
	if (!g->welcome_screen)
		handle_error(ERR_INV_PATH, g, NULL, 1);
	g->scaled_welcome.i = NULL;
	g->is_paused = 1;
	g->was_paused = 0;
}

/**
 * @brief Initializes the minimap based on game map dimensions.
 *
 * @param g Pointer to the game structure.
 */
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

/**
 * @brief Initializes various attributes for the game, including
 * window and images.
 *
 * @param g Pointer to the game structure.
 */
void	init_attr(t_game *g)
{
	g->window_width = WIN_W;
	g->window_height = WIN_H;
	g->win_ptr = mlx_new_window(g->mlx_ptr, g->window_width, g->window_height,
			"Cub3D");
	g->win_img.i = mlx_new_image(g->mlx_ptr, g->window_width, g->window_height);
	g->win_img.addr = mlx_get_data_addr(g->win_img.i, &g->win_img.bpp,
			&g->win_img.line_len, &g->win_img.endian);
	init_minimap(g);
	g->pl.speed = 0.02;
}

/**
 * @brief Initializes the game structure and loads the map.
 *
 * This function sets up the game by initializing the `t_game` structure 
 * and then reads the map from the specified file to populate the game state.
 *
 * @param g Pointer to the `t_game` structure to be initialized.
 * @param filename Name of the file containing the map data.
 */
void	init_game(t_game *g, char *filename)
{
	*g = cub_init();
	read_map(filename, g);
}
