/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse1_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:06:13 by noel-baz          #+#    #+#             */
/*   Updated: 2025/09/07 16:23:20 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	set_player_facing_direction(t_game *game, char direction_char)
{
	if (direction_char == 'N')
		game->direction = M_PI / 2;
	if (direction_char == 'S')
		game->direction = (3 * M_PI) / 2;
	if (direction_char == 'W')
		game->direction = M_PI;
	if (direction_char == 'E')
		game->direction = 0;
}

int	is_player_character(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_valid_map_character(char c, t_map *map, int y, int x)
{
	if (c == 'D')
	{
		if ((map->grid[y + 1][x] != '1' || map->grid[y - 1][x] != '1')
			&& (map->grid[y][x + 1] != '1' || map->grid[y][x - 1] != '1'))
			return (0);
	}
	if (c != '1' && c != '0' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != ' ' && c != 'D')
		return (0);
	return (1);
}

int	count_player(t_game *game, t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	(1) && (i = -1, player_count = 0);
	while (++i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!is_valid_map_character(map->grid[i][j], map, i, j))
				return (-1);
			if (is_player_character(map->grid[i][j]))
			{
				set_player_facing_direction(game, map->grid[i][j]);
				player_count++;
			}
			j++;
		}
	}
	return (player_count);
}
