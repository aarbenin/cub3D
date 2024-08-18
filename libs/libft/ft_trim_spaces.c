/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:27:06 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/08 10:30:19 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	trim_spaces(char *line, int *col_start, int *col_end)
{
	int	length;

	length = ft_strlen(line);
	*col_start = 0;
	while (*col_start < length && line[*col_start] == ' ')
		(*col_start)++;
	*col_end = length - 1;
	while (*col_end > *col_start && line[*col_end] == ' ')
		(*col_end)--;
}
