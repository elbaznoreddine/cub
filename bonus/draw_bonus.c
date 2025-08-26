/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:00:32 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/23 16:28:43 by noel-baz         ###   ########.fr       */
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

void	draw_line0(t_list *list, double y, double x)
{
	double	dy;
	double	dx;
	double	step;

	dy = y - list->py;
	dx = x - list->px;
	step = fmax(fabs(dx), fabs(dy));
	if (step != 0)
		draw_line01(list, dy, dx, step);
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
			if (list->line[y][x] == 'N' | list->line[y][x] == 'E' | list->line[y][x] == 'W' | list->line[y][x] == 'S')
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
