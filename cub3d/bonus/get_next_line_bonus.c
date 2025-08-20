/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:28:29 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/31 09:25:25 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	s1len;
	size_t	ptrlen;

	if (!s1 && !s2)
		return (0);
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	s1len = ft_strlen(s1);
	ptrlen = s1len + ft_strlen(s2) + 1;
	ptr = malloc(sizeof(char) * ptrlen);
	if (!ptr)
		return (free(s1), s1 = 0, s1);
	ft_strlcpy(ptr, s1, s1len + 1);
	ft_strlcat(&ptr[s1len], s2, ptrlen);
	return (free(s1), s1 = 0, ptr);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	slen;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (0);
	slen = ft_strlen(&s[start]);
	if (len > slen)
		len = slen;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, &s[start], len + 1);
	return (ptr);
}

int	ft_readline(int fd, char **buff, char **ptr)
{
	int	i;

	*buff = malloc(sizeof(char) * ((size_t) BUFFER_SIZE + 1));
	if (!(*buff))
		return (0);
	while (ft_strchr(*ptr, '\n') == -1)
	{
		i = read(fd, *buff, BUFFER_SIZE);
		if (i == -1)
			return (0);
		if (i == 0)
			break ;
		(*buff)[i] = '\0';
		*ptr = ft_strjoin(*ptr, *buff);
		if (!(*ptr))
			return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*ptr;
	char		*buff;
	int			i;

	if (fd == -10)
		return (free(ptr), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!ft_readline(fd, &buff, &ptr))
		return (free(buff), buff = 0, free(ptr), ptr = 0, ptr);
	free(buff);
	buff = 0;
	i = ft_strchr(ptr, '\n');
	if (i == -1)
	{
		buff = ft_substr(ptr, 0, ft_strlen(ptr) + 1);
		return (free(ptr), ptr = 0, buff);
	}
	buff = ft_substr(ptr, 0, i + 1);
	if (!buff)
		return (free(ptr), ptr = 0, ptr);
	if (ptr[i + 1] == '\0')
		return (free(ptr), ptr = 0, buff);
	ft_strlcpy(ptr, &ptr[i + 1], ft_strlen(&ptr[i + 1]) + 1);
	return (buff);
}
