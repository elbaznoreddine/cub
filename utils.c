/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:33:13 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/23 13:11:31 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

double	dis(t_list *list, double y, double x)
{
	return (sqrt((x - list->px) * (x - list->px) + \
	(y - list->py) * (y - list->py)));
}

void	ft_free(char **ptr)
{
	size_t	i;

	i = 0;
	if (ptr && ptr[i])
		while (ptr[i])
			free(ptr[i++]);
	if (ptr)
	{
		free(ptr);
		ptr = 0;
	}
}

void	set_var(t_list *list)
{
	list->up = 1;
	list->left = 0;
	list->hhit = 0;
	list->vhit = 0;
	list->hwallx = 0;
	list->hwally = 0;
	list->vwallx = 0;
	list->vwally = 0;
}

void	reset_ang(t_list *list, double *v)
{
	if (*v > 2 * list->pi)
		*v -= 2 * list->pi;
	if (*v < 0)
		*v += 2 * list->pi;
}
