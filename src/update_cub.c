/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:33:07 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/19 11:52:48 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

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
    if (g->frame_count == 0)
    {
        init_ray(g);
    }
    if (!(g->frame_count % g->rate))
    {
        if (!(g->frame_count % (10 * g->rate)))
            g->pl.door_cooldown = 0;
        cast_rays(g);
        redraw_elem(g, *g->scope, WIN_W / 2 - g->scope->width / 2, WIN_H / 2 - g->scope->height / 2);
        redraw_elem(g, g->miniview, WIN_W - g->miniview.width - 20, WIN_H - g->miniview.height - 20);
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