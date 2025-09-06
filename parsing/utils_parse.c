/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:08:31 by noel-baz          #+#    #+#             */
/*   Updated: 2025/09/06 10:08:32 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	init_game(t_game **game)
{
	*game = malloc(sizeof(t_game));
	if (!*game)
		return (0);
	(*game)->map = NULL;
	(*game)->config = NULL;
	return (1);
}

int	ft_check_map_extension(char *exten)
{
	size_t	len;

	len = ft_strlen(exten) - 4;
	if (!ft_strcmp(exten + len, ".cub"))
		return (1);
	return (0);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

void	free_config(t_config *config)
{
	if (!config)
		return ;
	if (config->path_north)
		free(config->path_north);
	if (config->path_south)
		free(config->path_south);
	if (config->path_west)
		free(config->path_west);
	if (config->path_east)
		free(config->path_east);
	if (config->floor)
		free(config->floor);
	if (config->ceil)
		free(config->ceil);
	free(config);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
		free_map(game->map);
	if (game->config)
		free_config(game->config);
	free(game);
}
