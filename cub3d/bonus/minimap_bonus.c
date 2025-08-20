/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:26:12 by yzoullik          #+#    #+#             */
/*   Updated: 2025/07/31 09:25:30 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_1(int x, int y, t_list *list)
{
	int	ey;
	int	ex;
	int	i;

	i = 1;
	ey = y + list->tail;
	ex = x + list->tail;
	if (ey == 0)
		ey = list->tail;
	if (ex == 0)
		ex = list->tail;
	while (y + i < ey)
	{
		if (ex == list->tail)
			x = 0;
		else
			x = ex - list->tail;
		while (x + i < ex)
		{
			mlx_put_pixel(list->win, x * list->f, y * list->f, \
			get_rgba(0, 0, 0, 255));
			x++;
		}
		y++;
	}
}

void	draw_0(int x, int y, t_list *list)
{
	int	ey;
	int	ex;
	int	i;

	i = 1;
	ey = y + list->tail;
	ex = x + list->tail;
	if (ey == 0)
		ey = list->tail;
	if (ex == 0)
		ex = list->tail;
	while (y + i < ey)
	{
		if (ex == list->tail)
			x = 0;
		else
			x = ex - list->tail;
		while (x + i < ex)
		{
			mlx_put_pixel(list->win, x * list->f, y * list->f, \
			get_rgba(255, 255, 255, 255));
			x++;
		}
		y++;
	}
}

void	draw_line(t_list *list, double wally, double wallx, double v)
{
	double	y;
	double	x;
	double	vy;
	double	vx;

	y = list->py;
	x = list->px;
	vy = sin(v);
	vx = cos(v);
	(void)(wally);
	(void)(wallx);
	while (x >= 0 && x <= list->ww && y >= 0 && y <= list->wh)
	{
		if (is_wall(list, y, x))
			break ;
		mlx_put_pixel(list->win, x * list->f, y * list->f, \
		get_rgba(255, 0, 0, 255));
		y -= vy;
		x -= vx;
	}
}

void	draw_cir(t_list *list)
{
	int	i;
	int	r;
	int	y;
	int	x;

	r = 0;
	while (r < 6)
	{
		i = 0;
		while (i < 360)
		{
			x = r * cos(i * list->pi / 180);
			y = r * sin(i * list->pi / 180);
			mlx_put_pixel(list->win, (list->px + x) * list->f, \
			(list->py + y) * list->f, get_rgba(255, 0, 0, 255));
			i++;
		}
		r++;
	}
}
