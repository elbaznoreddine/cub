/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:23:22 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/06 15:22:07 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	h_dda(t_list *list, double nexty, double nextx)
{
	double	x;
	double	y;

	while (1)
	{
		x = nextx;
		y = nexty;
		if (list->up)
			y -= 1;
		if (nextx < 0 || nextx > list->ww || nexty < 0 || nexty > list->wh)
			return ;
		if (is_wall(list, y, x))
		{
			list->hwally = nexty;
			list->hwallx = nextx;
			list->hhit = 1;
			return ;
		}
		nexty += list->ystep;
		nextx += list->xstep;
		list->hwally = nexty;
		list->hwallx = nextx;
	}
}

void	v_dda(t_list *list, double nexty, double nextx)
{
	double	x;
	double	y;

	while (1)
	{
		x = nextx;
		y = nexty;
		if (list->left)
			x -= 1;
		if (nextx < 0 || nextx > list->ww || nexty < 0 || nexty > list->wh)
			return ;
		if (is_wall(list, y, x))
		{
			list->vhit = 1;
			list->vwally = nexty;
			list->vwallx = nextx;
			return ;
		}
		nexty += list->ystep;
		nextx += list->xstep;
		list->vwally = nexty;
		list->vwallx = nextx;
	}
}

void	h_p(t_list *list, double v, double *y, double *x)
{
	*y = floor(list->py / list->tail) * list->tail;
	if (!list->up)
		*y += list->tail;
	*x = ((*y - list->py) / tan(v)) + list->px;
	if (list->up)
		list->ystep = list->tail * -1;
	else
		list->ystep = list->tail;
	list->xstep = list->ystep / tan(v);
}

void	v_p(t_list *list, double v, double *y, double *x)
{
	*x = floor(list->px / list->tail) * list->tail;
	if (!list->left)
		*x += list->tail;
	*y = list->py + ((*x - list->px) * tan(v));
	if (!list->left)
		list->xstep = list->tail;
	else
		list->xstep = list->tail * -1;
	list->ystep = list->xstep * tan(v);
}
