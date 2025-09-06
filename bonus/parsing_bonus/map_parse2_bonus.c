/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:06:16 by noel-baz          #+#    #+#             */
/*   Updated: 2025/09/06 10:37:58 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	space_touches_empty_cell(t_map *map, int i, int j)
{
	if (map->grid[i][j] == ' ')
	{
		if ((j < map->width - 1 && map->grid[i][j + 1] == '0') ||
			(j > 0 && map->grid[i][j - 1] == '0') ||
			(i < map->height - 1 && map->grid[i + 1][j] == '0') ||
			(i > 0 && map->grid[i - 1][j] == '0'))
			return (1);
		if ((j < map->width - 1 && map->grid[i][j + 1] == 'D') ||
			(j > 0 && map->grid[i][j - 1] == 'D') ||
			(i < map->height - 1 && map->grid[i + 1][j] == 'D') ||
			(i > 0 && map->grid[i - 1][j] == 'D'))
			return (1);
	}
	return (0);
}

int	has_invalid_border_character(char c)
{
	if (c != '1' && c != ' ')
		return (1);
	return (0);
}

int	is_border_position(int i, int j, t_map *map)
{
	if (i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1)
		return (1);
	return (0);
}

int	config_type(char *line, int i, int j)
{
	if (!ft_strncmp(line + i, "NO", j))
		return (1);
	if (!ft_strncmp(line + i, "SO", j))
		return (2);
	if (!ft_strncmp(line + i, "WE", j))
		return (3);
	if (!ft_strncmp(line + i, "EA", j))
		return (4);
	if (!ft_strncmp(line + i, "F", j))
		return (5);
	if (!ft_strncmp(line + i, "C", j))
		return (6);
	return (-1);
}
