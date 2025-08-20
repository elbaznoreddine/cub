/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:52:14 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/31 09:25:35 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_isspace(char c)
{
	if (c == '\n')
		return (1);
	return (0);
}

size_t	ft_strcount(char const *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]) && (ft_isspace(s[i + 1]) || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

size_t	ft_chrcount(char const *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			j++;
		if (!ft_isspace(s[i]) && (ft_isspace(s[i + 1]) || s[i + 1] == '\0'))
			return (j);
		i++;
	}
	return (j);
}

int	ft_solve(char const *s, char *str, char **ptr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (j == 0 && !ft_isspace(s[i]))
		{
			str = malloc(sizeof(char) * (ft_chrcount(&s[i]) + 1));
			if (!str)
				return (0);
		}
		if (!ft_isspace(s[i]))
			str[j++] = s[i];
		if (!ft_isspace(s[i]) && (ft_isspace(s[i + 1]) || s[i + 1] == '\0'))
		{
			str[j] = '\0';
			*ptr++ = str;
			j = 0;
		}
		i++;
	}
	*ptr = 0;
	return (1);
}

char	**ft_split(char const *s)
{
	char	**ptr;
	char	*str;

	if (!s)
		return (0);
	ptr = malloc(sizeof(char *) * (ft_strcount(s) + 1));
	if (!ptr)
		return (0);
	str = 0;
	if (!ft_solve(s, str, ptr))
		return (ft_free(ptr), free(str), str = 0, ptr);
	return (ptr);
}
