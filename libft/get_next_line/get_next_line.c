/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:59:11 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/07 15:40:23 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(int fd, char buf[OPEN_MAX][BUFFER_SIZE], char *line)
{
	ssize_t		i;

	i = 0;
	while (buf[fd][i] != '\0')
	{
		if (buf[fd][i] == '\n')
		{
			line = ft_strnjoin_free_s1(line, buf[fd], i + 1);
			ft_memmove(buf[fd], buf[fd] + i + 1, BUFFER_SIZE - i - 1);
			buf[fd][BUFFER_SIZE - i - 1] = '\0';
			return (line);
		}
		i++;
	}
	line = ft_strnjoin_free_s1(line, buf[fd], i);
	buf[fd][0] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buf[OPEN_MAX][BUFFER_SIZE];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		if (buf[fd][0] == '\0')
		{
			bytes_read = read(fd, buf[fd], BUFFER_SIZE);
			if (bytes_read <= 0)
			{
				if (line && *line)
					return (line);
				free(line);
				return (NULL);
			}
			buf[fd][bytes_read] = '\0';
		}
		line = extract_line(fd, buf, line);
		if (line)
			return (line);
	}
}
