/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogoman <ogoman@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 06:34:55 by ogoman            #+#    #+#             */
/*   Updated: 2024/08/09 12:15:05 by ogoman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*buf[4096];
	char		*line;
	size_t		old_len;

	if (fd < 0 || fd > 4095 || BUFFER_SIZE < 0)
		return (NULL);
	line = NULL;
	if (gnl_strchr_i(buf[fd], '\n') == -1)
	{
		old_len = gnl_strlen(buf[fd]);
		buf[fd] = gnl_expand_buffer(buf[fd], fd);
		if (old_len == gnl_strlen(buf[fd]) && buf[fd])
			line = gnl_substr(buf[fd], 0, gnl_strlen(buf[fd]));
	}
	if (!buf[fd])
		return (NULL);
	if (!line && gnl_strchr_i(buf[fd], '\n') != -1)
		line = gnl_substr(buf[fd], 0, gnl_strchr_i(buf[fd], '\n') + 1);
	if (line)
	{
		buf[fd] = gnl_shrink_buffer(buf[fd], line);
		return (line);
	}
	return (get_next_line(fd));
}

char	*gnl_shrink_buffer(char *buf, char *line)
{
	char	*newbuf;
	int		line_len;

	if (!buf || !line)
		return (buf);
	line_len = gnl_strlen(line);
	if ((int)gnl_strlen(buf) == line_len)
	{
		free(buf);
		return (NULL);
	}
	newbuf = gnl_substr(buf, line_len, gnl_strlen(buf) - line_len);
	free(buf);
	return (newbuf);
}

char	*gnl_expand_buffer(char *buf, int fd)
{
	char	*newbuf;
	int		newlen;
	char	*updated_map;

	updated_map = gnl_newread(fd);
	if (!updated_map)
		return (NULL);
	if (!updated_map[0])
	{
		free(updated_map);
		return (buf);
	}
	if (!buf)
		return (updated_map);
	newlen = gnl_strlen(buf) + gnl_strlen(updated_map);
	newbuf = malloc(newlen + 1);
	if (!newbuf)
		return (NULL);
	gnl_strlcpy(newbuf, buf, newlen + 1);
	gnl_strlcat(newbuf, updated_map, newlen + 1);
	free(buf);
	free(updated_map);
	return (newbuf);
}

char	*gnl_newread(int fd)
{
	char	*updated_map;
	int		nbytes;

	updated_map = malloc(BUFFER_SIZE + 1);
	if (!updated_map)
		return (NULL);
	nbytes = read(fd, updated_map, BUFFER_SIZE);
	if (nbytes < 0)
	{
		free(updated_map);
		return (NULL);
	}
	updated_map[nbytes] = '\0';
	return (updated_map);
}
