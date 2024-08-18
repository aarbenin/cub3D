/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 10:53:35 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/08 10:23:12 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	size_t	i;
	void	*new_ptr;

	i = 0;
	new_ptr = malloc(new_size);
	if (new_size <= old_size)
	{
		return (ptr);
	}
	if (new_ptr == NULL)
	{
		return (NULL);
	}
	while (i < old_size)
	{
		((char *)new_ptr)[i] = ((char *)ptr)[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}
