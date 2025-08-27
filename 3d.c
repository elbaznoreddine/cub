/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:38:58 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/27 11:19:36 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

mlx_texture_t	*get_wall_texture(t_list *list, double ray_angle)
{
	double	ray_x;
	double	ray_y;
	int		side;

	ray_x = cos(ray_angle);
	ray_y = sin(ray_angle);
	if (list->hd < list->vd)
		side = 1;
	else
		side = 0;
	if (side == 1)
	{
		if (ray_y > 0)
			return (list->north_texture);
		else
			return (list->south_texture);
	}
	else
	{
		if (ray_x > 0)
			return (list->west_texture);
		else
			return (list->east_texture);
	}
}

void	draw_3dwall(t_list *list, int i, double v)
{
	int	z;

	z = 0;
	while (z < list->h / 2)
	{
		mlx_put_pixel(list->win, i, z, list->game->ceil);
		z++;
	}
	while (z < list->h)
	{
		mlx_put_pixel(list->win, i, z, list->game->floor);
		z++;
	}
	draw_wall_texture(list, i, v);
}

void	draw_3d(t_list *list, double d, double v, int i)
{
	double	dp;
	double	wh;
	int		wsh;
	int		top;
	int		down;

	d *= cos(v - list->v);
	dp = (list->w / 2) / tan(list->fov / 2);
	wh = (list->tail / d) * dp;
	wsh = (int)wh;
	top = (list->h / 2) - (wsh / 2);
	down = (list->h / 2) + (wsh / 2);
	if (wsh <= 1)
	{
		top = list->h / 2;
		down = top + 1;
	}
	list->top = top;
	list->down = down;
	draw_3dwall(list, i, v);
}

void	draw_wall(t_list *list, double v, double i)
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
	draw_3d(list, d, v, i);
}

void	draw_p(t_list *list)
{
	double	x;
	double	y;
	double	i;
	double	v;

	i = 0;
	v = list->v - (list->fov / 2);
	while (i < list->w)
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
		draw_wall(list, v, i);
		v += (list->fov / list->w);
		i++;
	}
}
