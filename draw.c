/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:00:32 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/27 12:04:55 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	is_wall(t_list *list, double y, double x)
{
	double	j;
	double	i;

	if (x < 0 || x > list->ww || y < 0 || y > list->wh)
		return (1);
	j = floor(y / list->tail);
	i = floor(x / list->tail);
	if (list->line[(int) j][(int) i] == '1' || (list->line[(int) j][(int) i] == 32))
		return (1);
	return (0);
}

int	to_move(t_list *list, double y, double x)
{
	int		i;
	double	px;
	double	py;

	i = 0;
	py = list->py;
	px = list->px;
	if (is_wall(list, py + (y * 20), px + (x * 20)) > 0)
		return (0);
	if (is_wall(list, py + (y * 20) + 5, px + (x * 20)) > 0)
		return (0);
	if (is_wall(list, py + (y * 20) - 5, px + (x * 20)) > 0)
		return (0);
	if (is_wall(list, py + (y * 20), px + (x * 20) + 5) > 0)
		return (0);
	if (is_wall(list, py + (y * 20), px + (x * 20) - 5) > 0)
		return (0);
	while (i < list->mspeed)
	{
		py += y;
		px += x;
		if (is_wall(list, py, px))
			return (0);
		if (is_wall(list, py + 1, px))
			return (0);
		if (is_wall(list, py - 1, px))
			return (0);
		if (is_wall(list, py, px + 1))
			return (0);
		if (is_wall(list, py, px - 1))
			return (0);
		i++;
	}
	return (1);
}
