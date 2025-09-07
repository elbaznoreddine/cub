/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:19:23 by yzoullik          #+#    #+#             */
/*   Updated: 2025/09/07 15:06:45 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

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

void	open_door(t_list *list)
{
	int	x;
	int	y;

	x = floor(list->px / list->tail);
	y = floor(list->py / list->tail);
	if (list->line[y + 1][x] == 'D')
		list->line[y + 1][x] = 'd';
	if (list->line[y - 1][x] == 'D')
		list->line[y - 1][x] = 'd';
	if (list->line[y][x + 1] == 'D')
		list->line[y][x + 1] = 'd';
	if (list->line[y][x - 1] == 'D')
		list->line[y][x - 1] = 'd';
}

void	close_door(t_list *list)
{
	int	x;
	int	y;

	x = floor(list->px / list->tail);
	y = floor(list->py / list->tail);
	if (list->line[y + 1][x] == 'd')
		list->line[y + 1][x] = 'D';
	if (list->line[y - 1][x] == 'd')
		list->line[y - 1][x] = 'D';
	if (list->line[y][x + 1] == 'd')
		list->line[y][x + 1] = 'D';
	if (list->line[y][x - 1] == 'd')
		list->line[y][x - 1] = 'D';
}

void	move(mlx_key_data_t keydata, void	*param)
{
	t_list	*list;

	list = param;
	mlx_set_cursor_mode(list->mlx, MLX_MOUSE_HIDDEN);
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS
		&& !list->mouse_flag)
		list->mouse_flag = 1;
	if (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS
		&& list->mouse_flag)
		mlx_cursor_hook(list->mlx, &mouse, list);
	if (keydata.key == MLX_KEY_K && keydata.action == MLX_PRESS
		&& list->mouse_flag)
		list->mouse_flag = 0;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_close(list);
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
		open_door(list);
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		close_door(list);
}
