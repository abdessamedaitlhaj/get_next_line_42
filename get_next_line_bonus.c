/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-lha <aait-lha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:47:21 by aait-lha          #+#    #+#             */
/*   Updated: 2024/02/12 21:35:29 by aait-lha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*right_str(char *st_var)
{
	char	*right_str;
	int		i;
	int		j;

	i = 0;
	while (st_var[i] && st_var[i] != '\n')
		i++;
	if (!st_var[i])
		return (free(st_var), st_var = NULL, NULL);
	right_str = malloc(sizeof(char) * (ft_strlen(st_var) - i + 1));
	if (!right_str)
		return (free(st_var), st_var = NULL, NULL);
	i++;
	j = 0;
	while (st_var[i])
	{
		right_str[j] = st_var[i];
		i++;
		j++;
	}
	right_str[j] = '\0';
	free(st_var);
	return (right_str);
}

static char	*extract_line(char *st_var)
{
	char	*line;
	int		i;

	i = 0;
	if (!st_var[i])
		return (NULL);
	while (st_var[i] && st_var[i] != '\n')
		i++;
	if (st_var[i] == '\n')
	{
		line = malloc(sizeof(char) * (i + 2));
		if (!line)
			return (NULL);
		line[i] = st_var[i];
		line[i + 1] = '\0';
		i = 0;
		while (st_var[i] && st_var[i] != '\n')
		{
			line[i] = st_var[i];
			i++;
		}
	}
	else
		line = ft_strdup(st_var);
	return (line);
}

static char	*read_line(int fd, char *st_var)
{
	char	*buffer;
	int		nb_bytes;

	nb_bytes = 1;
	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(st_var), st_var = NULL, NULL);
	while (nb_bytes != 0 && !ft_strchr(st_var, '\n'))
	{
		nb_bytes = read(fd, buffer, BUFFER_SIZE);
		if (nb_bytes == -1)
		{
			free(buffer);
			return (free(st_var), st_var = NULL, NULL);
		}
		buffer[nb_bytes] = '\0';
		st_var = ft_strjoin(st_var, buffer);
		if (!st_var)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (st_var);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*st_var[OPEN_MAX];

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	st_var[fd] = read_line(fd, st_var[fd]);
	if (!st_var[fd])
		return (NULL);
	line = extract_line(st_var[fd]);
	if (!line)
		return (free(st_var[fd]), st_var[fd] = NULL, NULL);
	st_var[fd] = right_str(st_var[fd]);
	return (line);
}
