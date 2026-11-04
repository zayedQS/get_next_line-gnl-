/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhasan <zhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 13:50:29 by zhasan            #+#    #+#             */
/*   Updated: 2026/11/04 17:00:00 by zhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_line(char *left_str)
{
	char	*line;
	int		i;

	i = 0;
	if (!left_str || !left_str[i])
		return (NULL);
	while (left_str[i] && left_str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + (left_str[i] == '\n') + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
	{
		line[i] = left_str[i];
		i++;
	}
	if (left_str[i] == '\n')
	{
		line[i] = left_str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*read_to_left_str(int fd, char *left_str)
{
	char	*buffer;
	char	*temp;
	int		bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&left_str));
	bytes = 1;
	while (!ft_strchr(left_str, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			ft_free(&buffer);
			return (ft_free(&left_str));
		}
		buffer[bytes] = '\0';
		temp = ft_strjoin(left_str, buffer);
		left_str = temp;
	}
	ft_free(&buffer);
	return (left_str);
}

static char	*obtain_remaining(char *left_str)
{
	char	*new_left_str;
	int		i;
	int		j;

	i = 0;
	while (left_str[i] && left_str[i] != '\n')
		i++;
	if (!left_str[i])
		return (ft_free(&left_str));
	new_left_str = malloc(sizeof(char) * (ft_strlen(left_str) - i + 1));
	if (!new_left_str)
		return (ft_free(&left_str));
	i++;
	j = 0;
	while (left_str[i])
		new_left_str[j++] = left_str[i++];
	new_left_str[j] = '\0';
	ft_free(&left_str);
	return (new_left_str);
}

char	*get_next_line(int fd)
{
	static char	*left_str[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	left_str[fd] = read_to_left_str(fd, left_str[fd]);
	if (!left_str[fd])
		return (NULL);
	line = extract_line(left_str[fd]);
	if (!line)
	{
		ft_free(&left_str[fd]);
		return (NULL);
	}
	left_str[fd] = obtain_remaining(left_str[fd]);
	return (line);
}
