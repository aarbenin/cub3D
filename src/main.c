/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:47:08 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/29 08:27:31 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"


int main(int ac, char **av)
{
    t_game g;

    // Проверка количества аргументов и расширения файла
    check_file(ac, av);
    init_game(&g, av[1]);
    validate_textures(&g);
    validate_colors(&g);
    // Преобразование карты и проверка карты
    char **updated_map = alight_map_rows(&g);
    ft_free_matrix(&g.map);
    g.map = updated_map;
    check_map(&g);
    setup_game(&g);
    return (0);
}
