/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:57:14 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/15 14:37:32 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "get_next_line.h"
#include "libft.h"

int	line_count(int fd)
{
	char	buf[BUFFER_SIZE];
	int		counter;
	int		b_read;
	int		i;

	counter = 0;
	b_read = 1;
	while (b_read)
	{
		i = 0;
		b_read = read(fd, buf, BUFFER_SIZE);
		if (b_read < 0)
			return (0);
		while (i < b_read)
		{
			if (buf[i] == '\n')
				counter++;
			i++;
		}
	}
	return (counter);
}

char	*expand_tabs(char *str)
{
	int		i;
	int		j;
	char	*exp;

	i = 0;
	j = 0;
	exp = malloc((ft_strlen(str) * 4) + 1);
	if (!exp)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\t')
		{
			exp[j++] = ' ';
			exp[j++] = ' ';
			exp[j++] = ' ';
			exp[j++] = ' ';
			i++;
		}
		else
			exp[j++] = str[i++];
	}
	free(str);
	exp[j] = '\0';
	return (exp);
}

char	**get_map(int fd, int lines)
{
	char	**map;
	int		i;
	char	*line;

	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	if (!line)
	{
		free(map);
		return (NULL);
	}
	while (line != NULL)
	{
		if (!empty(line))
			map[i++] = expand_tabs(line);
		else
			free(line);
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

char	**map_from_file(char *filename, char **map)
{
	int	filefd;
	int	linecount;

	filefd = open(filename, O_RDONLY);
	if (filefd < 0)
		return (NULL);
	linecount = line_count(filefd);
	close(filefd);
	if (linecount < 6)
	{
		printf("Error\nMap might be empty\n");
		return (NULL);
	}
	filefd = open(filename, O_RDONLY);
	if (filefd < 0)
		return (NULL);
	map = get_map(filefd, linecount + 1);
	return (map);
}
