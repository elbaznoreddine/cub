/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw0_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:06:16 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/31 17:01:25 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_mini_wall(t_list *list)
{
	double	x;
	double	y;
	double	d;

	x = 0;
	y = 0;
	list->hd = 1000000;
	list->vd = 1000000;
	if (list->hhit)
		list->hd = dis(list, list->hwally, list->hwallx);
	if (list->vhit)
		list->vd = dis(list, list->vwally, list->vwallx);
	if (list->hd < list->vd)
	{
		x = list->hwallx;
		y = list->hwally;
		d = list->hd;
	}
	else
	{
		x = list->vwallx;
		y = list->vwally;
		d = list->vd;
	}
	draw_line0(list, y, x);
}

void	draw_mini_p(t_list *list)
{
	double	x;
	double	y;
	double	i;
	double	v;

	draw_cir(list);
	i = 0;
	v = list->v - (list->fov / 2);
	while (i < list->ww)
	{
		reset_ang(list, &v);
		y = 0;
		x = 0;
		set_var(list);
		if (v > 0 && v < list->pi)
			list->up = 0;
		if ((v > list->pi / 2 && v < 3 * (list->pi / 2)))
			list->left = 1;
		(h_p(list, v, &y, &x), h_dda(list, y, x));
		(v_p(list, v, &y, &x), v_dda(list, y, x));
		draw_mini_wall(list);
		v += (list->fov / list->ww);
		i++;
	}
}

void	draw_map0(t_list *list)
{
	int	x;
	int	y;

	y = 0;
	while (list->line[y])
	{
		x = 0;
		while (list->line[y][x])
		{
			if (list->line[y][x] == '1')
				draw_1(x * list->tail, y * list->tail, list);
			if (list->line[y][x] == '0' || list->line[y][x] == 'P')
				draw_0(x * list->tail, y * list->tail, list);
			x++;
		}
		y++;
	}
	draw_cir(list);
	draw_mini_p(list);
}
