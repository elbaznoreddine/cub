/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_move_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 13:08:44 by noel-baz          #+#    #+#             */
/*   Updated: 2025/09/06 13:11:37 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	to_move0(t_list *list, double y, double x)
{
	double	px;
	double	py;

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
	return (1);
}

int	to_move(t_list *list, double y, double x)
{
	int		i;
	double	px;
	double	py;

	i = 0;
	py = list->py;
	px = list->px;
	if (!to_move0(list, y, x))
		return (0);
	while (i++ < list->mspeed)
	{
		py += y;
		px += x;
		if (is_wall(list, py, px) > 0)
			return (0);
		if (is_wall(list, py + 1, px) > 0)
			return (0);
		if (is_wall(list, py - 1, px) > 0)
			return (0);
		if (is_wall(list, py, px + 1) > 0)
			return (0);
		if (is_wall(list, py, px - 1) > 0)
			return (0);
	}
	return (1);
}

void	mouse(double xpos, double ypos, void *param)
{
	t_list	*list;
	int		delta_x;

	(void)ypos;
	list = (t_list *)param;
	if (!list->mouse_flag)
		return ;
	delta_x = (int)xpos - (list->w / 2);
	if (abs(delta_x) > 2)
	{
		list->v += delta_x * list->mouse_sens;
		if (list->v > 2 * list->pi)
			list->v -= 2 * list->pi;
		if (list->v < 0)
			list->v += 2 * list->pi;
		list->vy = sin(list->v);
		list->vx = cos(list->v);
		mlx_set_mouse_pos(list->mlx, list->w / 2, list->h / 2);
	}
}

int	move0(t_list *list)
{
	if (mlx_is_key_down(list->mlx, MLX_KEY_W))
	{
		if (!to_move(list, list->vy, list->vx))
			return (0);
		list->py += list->vy * list->mspeed;
		list->px += list->vx * list->mspeed;
		return (1);
	}
	if (mlx_is_key_down(list->mlx, MLX_KEY_S))
	{
		if (!to_move(list, -list->vy, -list->vx))
			return (0);
		list->py -= list->vy * list->mspeed;
		list->px -= list->vx * list->mspeed;
		return (1);
	}
	return (0);
}

int	move1(t_list *list)
{
	double	ang;

	if (mlx_is_key_down(list->mlx, MLX_KEY_A))
	{
		ang = list->v - (90 * list->pi / 180);
		if (ang > 2 * list->pi)
			ang -= 2 * list->pi;
		if (ang < 0)
			ang += 2 * list->pi;
		if (!to_move(list, sin(ang), cos(ang)))
			return (0);
		list->py += sin(ang) * list->mspeed;
		list->px += cos(ang) * list->mspeed;
		return (1);
	}
	return (0);
}
