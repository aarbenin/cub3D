#include "../inc/cub3D.h"

/**
 * Handles key release events. Updates the game state based on the key released.
 * 
 * @param key The key that was released.
 * @param g A pointer to the game state.
 * @return Always returns 0.
 */
int cub_keydown(int k, t_game *g)
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

int cub_keyup(int k, t_game *g)
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