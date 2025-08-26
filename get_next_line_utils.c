/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:08:34 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/23 13:12:12 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize != 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strdup(char *s1)
{
	char	*ptr;
	size_t	s1len;

	s1len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (s1len + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, s1len + 1);
	return (ptr);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (!dst && !dstsize)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (dstlen > dstsize)
		return (srclen + dstsize);
	ft_strlcpy(&dst[dstlen], src, dstsize - dstlen);
	return (dstlen + srclen);
}

int	ft_strchr(char *s, int c)
{
	size_t	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return (i);
		i++;
	}
	return (-1);
}
