/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarbenin <aarbenin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:37:13 by aarbenin          #+#    #+#             */
/*   Updated: 2024/09/11 11:37:16 by aarbenin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	set_direction_north(t_player *pl)
{
	pl->dir_x = 0;
	pl->dir_y = -1;
	pl->plane_x = 0.66;
	pl->plane_y = 0;
}

static void	set_direction_south(t_player *pl)
{
	pl->dir_x = 0;
	pl->dir_y = 1;
	pl->plane_x = -0.66;
	pl->plane_y = 0;
}

static void	set_direction_east(t_player *pl)
{
	pl->dir_x = 1;
	pl->dir_y = 0;
	pl->plane_x = 0;
	pl->plane_y = 0.66;
}

static void	set_direction_west(t_player *pl)
{
	pl->dir_x = -1;
	pl->dir_y = 0;
	pl->plane_x = 0;
	pl->plane_y = -0.66;
}

void	set_player_direction(t_player *pl, char dir)
{
	if (dir == 'N')
		set_direction_north(pl);
	else if (dir == 'S')
		set_direction_south(pl);
	else if (dir == 'E')
		set_direction_east(pl);
	else if (dir == 'W')
		set_direction_west(pl);
}
