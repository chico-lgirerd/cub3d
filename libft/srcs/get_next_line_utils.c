/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgirerd <lgirerd@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:59:01 by lgirerd           #+#    #+#             */
/*   Updated: 2024/12/04 17:40:15 by lgirerd          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*ft_strjoin_mod(char *s1, char *s2)
{
	char	*res;
	int		s1_len;
	int		s2_len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = 0;
	while (s2[s2_len] != '\n' && s2[s2_len] != '\0')
		s2_len++;
	if (s2[s2_len] == '\n')
		s2_len++;
	res = malloc(s1_len + s2_len + 1);
	if (res == NULL)
		return (free(s1), NULL);
	if (s1)
		ft_strlcpy(res, s1, s1_len + 1);
	if (s2)
		ft_strlcpy(res + s1_len, s2, s2_len + 1);
	free(s1);
	return (res);
}

char	*ft_strdup_mod(const char *s)
{
	char	*dup;
	size_t	s_len;
	size_t	i;

	s_len = 0;
	while (s[s_len] != '\n' && s[s_len] != '\0')
		s_len++;
	if (s[s_len] == '\n')
		s_len++;
	dup = malloc(s_len + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	line_checker(char	*str)
{
	size_t	i;

	i = 0;
	if (ft_strlen(str + i) == 0)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
