/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:59:36 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/11 09:27:39 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"


/**
 * Handles errors by displaying an appropriate error message and performing necessary cleanup.
 * 
 * @param err The error code indicating the type of error that occurred.
 * @param g The game structure to be cleaned up if necessary.
 * @param info Optional additional information to be displayed along with the error message.
 * @param should_exit Flag indicating whether the program should exit after handling the error.
 * @return Always returns 1 if `should_exit` is true (indicates that an error occurred).
 */

int	handle_error(t_cub_err err, t_text_game *g, char *info, int should_exit)
{
	if (!should_exit)
		return (0);
	cleanup_game(g);
	write(2, "cub3d: ", 7 * (err != ERR_END));
	write(2, "invalid number of arguments\n", 28 * (err == ERR_INV_AC));
	write(2, "cub3D not run in root of the project\n", 37 * (err == ERR_INV_PATH));
	write(2, "file must be of .cub type\n", 26 * (err == ERR_INV_EXT));
	write(2, "error opening file: ", 20 * (err == ERR_INV_FILE));
	write(2, "file is empty\n", 14 * (err == ERR_EMPTY_FILE));
	write(2, "devide out of memory\n", 21 * (err == ERR_OUT_OF_MEMORY));
	write(2, "invalid color\n", 15 * (err == ERR_INV_COLOR));
	write(2, "map not surrounded by walls\n", 28 * (err == ERR_INV_WALL));
	write(2, "invalid map\n", 12 * (err == ERR_INV_MAP));
	write(2, "invalid character\n", 18 * (err == ERR_INV_CHARAC));
	write(2, "invalid texture file\n", 21 * (err == ERR_INV_TEX));
	write(2, "invalid number of players\n", 26 * (err == ERR_INV_PLAYER));
	ft_putendl_fd(info, 2);
	if (err == ERR_INV_AC && ft_putchar_fd('\n', 2))
		show_usage(1);
	if (err == ERR_END)
		exit(0);
	exit(1);
	return (1);
}

/**
 * Displays the usage instructions for the program and exits.
 * 
 * @param exit_code The exit code to return after displaying the usage information.
 */
void	show_usage(int exit_code)
{
	ft_putstr_fd("Cub3D\nA simple raycaster with MinilibX\n\n", 2);
	ft_putstr_fd("usage: cub3d <map_file.cub>\n", 2);
	exit(exit_code);
}

/**
 * Handles the end of the program by displaying an end-of-program error message and exiting.
 * 
 * @param param Optional parameter for error handling.
 * @return Always returns 0 (indicates successful termination).
 */

int	cub_exit(void *param)
{
	handle_error(ERR_END, param, NULL, 1);
	return (0);
}
