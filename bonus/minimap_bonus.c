/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:26:12 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/28 14:03:46 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

void	draw_miniplayer(t_list	*list)
{
	double	i;
	double	j;
	double	x;

	j = 195;
	while (j <= 205)
	{
		i = 195;
		while (i++ <= 205)
			mlx_put_pixel(list->win, i * list->f, j * list->f, \
			get_rgba(255, 0, 0, 255));
		j++;
	}
	x = 0;
	j = 200;
	i = 200;
	while (x++ <= 50)
	{
		if (is_wall(list, list->py + j - 200, list->px + i - 200) > 0)
			break ;
		mlx_put_pixel(list->win, i * list->f, j * list->f, \
		get_rgba(255, 0, 0, 255));
		i += cos(list->v);
		j += sin(list->v);
	}
}

void	draw_pixel(t_list *list, double i, double j, int s)
{
	if (s == 1)
		mlx_put_pixel(list->win, i * list->f, j * list->f, \
		get_rgba(0, 0, 0, 255));
	if (s == 2)
		mlx_put_pixel(list->win, i * list->f, j * list->f, \
		get_rgba(255, 0, 0, 255));
}

void	draw_minimap(t_list *list)
{
	double	y;
	double	x;
	double	i;
	double	j;

	j = 0;
	y = list->py - 200;
	while (j <= 400)
	{
		(1 && (i = 0, x = list->px - 200));
		while (i++ <= 400)
		{
			if (is_wall(list, y, x) == 1 || is_wall(list, y, x) == 2)
				draw_pixel(list, i, j, is_wall(list, y, x));
			else if (is_wall(list, y, x) == -3)
				mlx_put_pixel(list->win, i * list->f, j * list->f, \
				get_rgba(0, 255, 0, 255));
			else
				mlx_put_pixel(list->win, i * list->f, j * list->f, \
				get_rgba(128, 128, 128, 255));
			x++;
		}
		(1 && j++, y++);
	}
	draw_miniplayer(list);
}

int	is_door0(t_list *list)
{
	if (list->left)
		list->vwallx -= 1;
	else
		list->vwallx += 1;
	if (list->vwallx < 0 || list->vwallx >= list->ww || list->vwally < 0
		|| list->vwally >= list->wh)
		return (0);
	if (list->line[(int) floor(list->vwally / list->tail)][(int) \
	floor(list->vwallx / list->tail)] == 'D')
		return (1);
	return (0);
}

int	is_door(t_list *list)
{
	if (list->hd < list->vd)
	{
		if (list->up)
			list->hwally -= 1;
		else
			list->hwally += 1;
		if (list->hwallx < 0 || list->hwallx >= list->ww || list->hwally < 0
			|| list->hwally >= list->wh)
			return (0);
		if (list->line[(int) floor(list->hwally / list->tail)][(int) \
		floor(list->hwallx / list->tail)] == 'D')
			return (1);
	}
	else
		return (is_door0(list));
	return (0);
}
