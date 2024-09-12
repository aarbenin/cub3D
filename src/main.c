/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:47:08 by ogoman            #+#    #+#             */
/*   Updated: 2024/09/12 09:02:45 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/**
 * @brief The entry point of the cub3D program.
 *
 * This function performs initial checks and setup required for the cub3D game.
 * It validates command-line arguments, initializes the game, validates
 * textures
 * and colors, adjusts the map rows, and performs a final map check before
 * setting up the game.
 *
 * @param ac The argument count from the command line.
 * @param av The argument vector from the command line, where av[1] is
 * expected to be the map file.
 *
 * @return Returns 0 upon successful execution.
 */
int	main(int ac, char **av)
{
	t_game	g;
	char	**updated_map;

	check_file(ac, av);
	init_game(&g, av[1]);
	validate_textures(&g);
	validate_colors(&g);
	updated_map = alight_map_rows(&g);
	ft_free_matrix(&g.map);
	g.map = updated_map;
	check_map(&g);
	setup_game(&g);
	return (0);
}
