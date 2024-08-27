/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:33:07 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/27 10:27:18 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"
static void clear_image(t_img *img, int color)
{
    int x, y;

    for (y = 0; y < WIN_H; y++)
    {
        for (x = 0; x < WIN_W; x++)
        {
            put_pixel(img, x, y, color);
        }
    }
}

/**
 * Updates the game state and redraws elements on the window.
 * 
 * @param param A pointer to a t_text_game structure that contains game state information.
 * @return 0 on success.
 * 
 * This function is called periodically by the MLX main loop. It checks if the current frame count
 * is a multiple of the update rate. If so, it redraws the game elements and updates the window.
 * The function also handles the cooldown for the player's door action.
 */
int cub_update(void *param)
{
    t_text_game *g;

    g = (t_text_game *)param;

    if (!(g->nframes % g->rate))
    {
        if (!(g->nframes % (2 * g->rate)))
			update_anim(g);
		if (!(g->nframes % (10 * g->rate)))
			g->pl.door_cooldown = 0;
    
        // Очистка экрана перед рендерингом
        clear_image(&g->win_img, 0x000000); // Заполнение черным цветом

        // Обновляем положение и поворот игрока
        move_player(g);
        rotate_player(g);

        draw_background(g);
        // Выполняем Ray-Casting и рендерим сцену
        cast_rays(g);
        redraw_elem(g, *g->scope, WIN_W / 2 - g->scope->width / 2, WIN_H / 2 - g->scope->height / 2);

        // Отображаем новое изображение
        mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->win_img.i, 0, 0);
    }
    g->frame_count++;
    return (0);
}







/**
 * Redraws an image element onto the game window at specified coordinates.
 * 
 * @param g A pointer to a t_text_game structure that contains game state information.
 * @param img The image to be drawn.
 * @param x The x-coordinate where the image should be placed.
 * @param y The y-coordinate where the image should be placed.
 * 
 * This function places the specified image onto the game window at the given coordinates,
 * combining it with the existing window image. It uses a blending color of 0xFF000000
 * to ensure proper overlay.
 */
void	redraw_elem(t_text_game *g, t_img img, int x, int y)
{
	int		p[2];
	t_img	images[2];

	p[0] = x;
	p[1] = y;
	images[0] = img;
	images[1] = g->win_img;
	mlx_img_to_img(p, images, 0xFF000000);
}