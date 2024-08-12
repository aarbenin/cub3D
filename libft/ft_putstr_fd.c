/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:47:42 by ogoman            #+#    #+#             */
/*   Updated: 2024/07/11 06:22:20 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
		return ((int)write(fd, s, ft_strlen(s)));
	return (0);
}

// void	ft_putstr_fd(char *s, int fd)
// {
// 	if (s != NULL)
// 	{
// 		while (*s)
// 		{
// 			write(fd, s, 1);
// 			s++;
// 		}
// 	}
// }
