/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 07:49:38 by ogoman            #+#    #+#             */
/*   Updated: 2024/07/11 06:23:54 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	if (s != NULL)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
		return ((int)ft_strlen(s) + 1);
	}
	return (0);
}

// void	ft_putendl_fd(char *s, int fd)
// {
// 	if (s == 0 || fd == 0)
// 	{
// 		return ;
// 	}
// 	if (*s)
// 	{
// 		while (*s != 0)
// 		{
// 			write(fd, s, 1);
// 			s++;
// 		}
// 	}
// 	write(fd, "\n", 1);
// }
