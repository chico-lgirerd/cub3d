/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:58:28 by lgirerd           #+#    #+#             */
/*   Updated: 2024/12/04 17:45:21 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_bzero_mod(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		s[i] = 0;
		i++;
	}
}

static void	ft_cleaner(char *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		i++;
	j = 0;
	while (s[i + j])
	{
		s[j] = s[i + j];
		j++;
	}
	s[j] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = "\0";
	char		*line;
	int			b_read;

	b_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup_mod(buffer);
	if (!line)
		return (NULL);
	while (b_read && line_checker(line) == 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read < 0)
			return (ft_bzero_mod(buffer), free(line), NULL);
		buffer[b_read] = '\0';
		line = ft_strjoin_mod(line, buffer);
		if (!line)
			return (NULL);
	}
	ft_cleaner(buffer);
	if (line[0] == '\0')
		return (free(line), NULL);
	return (line);
}

// int	main(void)
// {
// 	int fd;
// 	char *line;

// 	fd = open("small.txt", O_RDONLY);
// 	printf("Contenu du fichier\n");
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
