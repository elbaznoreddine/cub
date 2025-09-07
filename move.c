/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:19:23 by yzoullik          #+#    #+#             */
/*   Updated: 2025/09/07 15:15:28 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	move11(t_list *list)
{
	double	ang;

	if (mlx_is_key_down(list->mlx, MLX_KEY_D))
	{
		ang = list->v + (90 * list->pi / 180);
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

int	move2(t_list *list)
{
	if (mlx_is_key_down(list->mlx, MLX_KEY_RIGHT))
	{
		list->v += list->rspeed;
		if (list->v > 2 * list->pi)
			list->v -= 2 * list->pi;
		list->vy = sin(list->v);
		list->vx = cos(list->v);
		return (1);
	}
	if (mlx_is_key_down(list->mlx, MLX_KEY_LEFT))
	{
		list->v -= list->rspeed;
		if (list->v < 0)
			list->v += 2 * list->pi;
		list->vy = sin(list->v);
		list->vx = cos(list->v);
		return (1);
	}
	return (0);
}

void	move(mlx_key_data_t keydata, void	*param)
{
	t_list	*list;

	list = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_close(list);
	if (move0(list) || move1(list) || move11(list) || move2(list))
		draw_p(list);
}
