/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:06:10 by noel-baz          #+#    #+#             */
/*   Updated: 2025/09/06 10:06:11 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D_bonus.h"

char	*ft_substr(char *s, unsigned int index, size_t bytes)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (index > ft_strlen(s))
		return (ft_strdup(""));
	if (bytes > ft_strlen(s) - index)
		bytes = ft_strlen(s) - index;
	str = malloc(bytes + 1);
	if (!str)
		return (NULL);
	while (bytes--)
	{
		str[i++] = s[index++];
	}
	str[i] = '\0';
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	if (len == 0)
		return (dst);
	i = 0;
	while (i < len - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (!str)
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i] && (str[i] <= '9' && str[i] >= '0'))
	{
		result = result * 10 + (str[i] - '0');
		if (result > 255)
			return (-1);
		i++;
	}
	if (str[i] == '\0')
		return (result);
	return (-1);
}
