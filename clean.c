/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 15:10:07 by noel-baz          #+#    #+#             */
/*   Updated: 2025/09/07 16:13:59 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	clean_close(t_list *list)
{
	(mlx_delete_texture(list->north_texture),
		mlx_delete_texture(list->south_texture),
		mlx_delete_texture(list->east_texture),
		mlx_delete_texture(list->west_texture));
	free_game(list->game);
	free(list);
	exit(0);
}

void	close_window(void	*param)
{
	t_list	*list;

	list = param;
	clean_close(list);
}
