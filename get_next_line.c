#include "get_next_line.h"

static char	*extract_line(char *left_str)
{
	char	*line;
	int		i;

	i = 0;
	if (!left_str[i])
		return (NULL);
	while (left_str[i] && left_str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + (left_str[i] == '\n' ? 2 : 1)));
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
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*read_to_left_str(int fd, char *left_str)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(left_str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(left_str);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(left_str, buffer);
		left_str = temp;
	}
	free(buffer);
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
	{
		free(left_str);
		return (NULL);
	}
	new_left_str = malloc(sizeof(char) * (ft_strlen(left_str) - i + 1));
	if (!new_left_str)
	{
		free(left_str);
		return (NULL);
	}
	i++;
	j = 0;
	while (left_str[i])
		new_left_str[j++] = left_str[i++];
	new_left_str[j] = '\0';
	free(left_str);
	return (new_left_str);
}

char	*get_next_line(int fd)
{
	static char	*left_str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (left_str)
		{
			free(left_str);
			left_str = NULL;
		}
		return (NULL);
	}
	left_str = read_to_left_str(fd, left_str);
	if (!left_str)
	
		return (NULL);
	line = extract_line(left_str);
	if (!line)
	{
		free(left_str);
		left_str = NULL;
		return (NULL);
	}
	left_str = obtain_remaining(left_str);
	return (line);
}


