/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 15:19:23 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/14 04:42:20 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	move0(t_list *list)
{
	if (mlx_is_key_down(list->mlx, MLX_KEY_W))
	{
		if (is_wall(list, list->py + (list->vy * list->mspeed), \
		list->px + (list->vx * list->mspeed)))
			return (0);
		list->py += list->vy * list->mspeed;
		list->px += list->vx * list->mspeed;
		return (1);
	}
	if (mlx_is_key_down(list->mlx, MLX_KEY_S))
	{
		if (is_wall(list, list->py - (list->vy * list->mspeed), \
			list->px - (list->vx * list->mspeed)))
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
		if (is_wall(list, list->py + (sin(ang) * list->mspeed), \
		list->px + (cos(ang) * list->mspeed)))
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
		if (is_wall(list, list->py + (sin(ang) * list->mspeed), \
		list->px + (cos(ang) * list->mspeed)))
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

void mouse(double xpos, double ypos, void *param)
{
    t_list *list = (t_list *)param;
    int delta_x;
    (void)ypos;
    // Calculate horizontal movement from center
    delta_x = (int)xpos - (list->w / 2);
    
    // Only process if there's significant movement
    if (abs(delta_x) > 2) {
        // Update player rotation based on mouse movement
        list->v += delta_x * list->mouse_sens;
        
        // Keep angle in valid range [0, 2*PI]
        if (list->v > 2 * list->pi)
            list->v -= 2 * list->pi;
        if (list->v < 0)
            list->v += 2 * list->pi;
        
        // Update direction vectors
        list->vy = sin(list->v);
        list->vx = cos(list->v);
        
        // Reset cursor to center
        mlx_set_mouse_pos(list->mlx, list->w / 2, list->h / 2);
    }
}

void	move(mlx_key_data_t keydata, void	*param)
{
	t_list	*list;

	list = param;
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS)
		exit(0);
	if (move0(list) || move1(list) || move11(list) || move2(list))
		return ;
}
