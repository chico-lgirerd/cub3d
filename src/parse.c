/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:57:14 by lgirerd           #+#    #+#             */
/*   Updated: 2025/10/01 12:54:14 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "get_next_line.h"

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

char	**get_map(t_world *world, int fd, int lines)
{
	(void)world;
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
		map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

char	**map_from_file(t_world *world, char *filename, char** map)
{
	int	filefd;
	int	linecount;
	
	filefd = open(filename, O_RDONLY);
	if (filefd < 0)
		return (NULL);
	linecount = line_count(filefd);
	close(filefd);
	filefd = open(filename, O_RDONLY);
	if (filefd < 0)
		return (NULL);
	if (linecount == 0)
		return (NULL);
	map = get_map(world, filefd, linecount + 1);
	return (map);
}