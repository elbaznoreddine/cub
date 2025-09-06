/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:00:32 by yzoullik          #+#    #+#             */
/*   Updated: 2025/09/06 13:06:38 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_line01(t_list *list, double dy, double dx, double step)
{
	double	stepy;
	double	stepx;
	double	i;

	i = 0;
	stepy = dy / step;
	stepx = dx / step;
	while (i <= step)
	{
		mlx_put_pixel(list->win, round(list->px + i * stepx) * list->f, \
		round(list->py + i * stepy) * list->f, get_rgba(255, 0, 0, 255));
		i++;
	}
}

void	draw_p0(t_list *list)
{
	int	x;
	int	y;

	y = 0;
	while (list->line[y])
	{
		x = 0;
		while (list->line[y][x])
		{
			if (list->line[y][x] == 'N' | list->line[y][x] == 'E'
				| list->line[y][x] == 'W' | list->line[y][x] == 'S')
			{
				list->py = y * list->tail + 32;
				list->px = x * list->tail + 32;
				draw_p(list);
				return ;
			}
			x++;
		}
		y++;
	}
}

int	is_wall(t_list *list, double y, double x)
{
	double	j;
	double	i;

	if (x < 0 || x >= list->ww || y < 0 || y >= list->wh)
		return (1);
	j = floor(y / list->tail);
	i = floor(x / list->tail);
	if (list->line[(int) j][(int) i] == '1'
		|| list->line[(int) j][(int) i] == 32)
		return (1);
	if (list->line[(int) j][(int) i] == 'D')
		return (2);
	if (list->line[(int) j][(int) i] == 'd')
		return (-3);
	return (0);
}
