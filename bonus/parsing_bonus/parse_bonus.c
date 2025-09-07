/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:06:23 by noel-baz          #+#    #+#             */
/*   Updated: 2025/09/07 16:23:10 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	validate_map_boundaries(t_map *map)
{
	int	i;
	int	j;

	if (!map || !map->grid || map->height <= 0 || map->width <= 0)
		return (0);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (is_border_position(i, j, map))
			{
				if (has_invalid_border_character(map->grid[i][j]))
					return (0);
			}
			if (space_touches_empty_cell(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_game *game, t_map *map)
{
	int	player_count;

	if (!map || !map->grid || map->height <= 0 || map->width <= 0)
		return (0);
	player_count = count_player(game, map);
	if (player_count != 1)
		return (0);
	return (1);
}

int	parse_map_section(t_game *game, int fd, char *first_map_line)
{
	if (!first_map_line)
		return (0);
	game->map = malloc(sizeof(t_map));
	if (!game->map)
		return (free(first_map_line), 0);
	game->map->grid = NULL;
	game->map->height = 0;
	game->map->width = 0;
	if (!read_entire_map_content(game, fd, first_map_line))
		return (free(first_map_line), 0);
	free(first_map_line);
	return (1);
}

int	parse_config(t_game *game, int fd, char **first_map_line)
{
	char	*line;
	int		element_type;
	int		process_result;

	game->config = malloc(sizeof(t_config));
	if (!game->config)
		return (0);
	(setup_empty_config(game->config), line = get_next_line(fd));
	while (line)
	{
		if (!line || line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		process_result = process_config_line(game, line, &element_type,
				first_map_line);
		if (process_result == 0)
			return (free(line), 0);
		if (process_result == 1)
			return (check_config_completeness(game->config));
		(free(line), line = get_next_line(fd));
	}
	return (check_config_completeness(game->config));
}

int	parse_complete_map_file(t_game *game, char *map_filename)
{
	int		fd;
	char	*first_map_line;

	first_map_line = NULL;
	fd = open(map_filename, O_RDONLY);
	if (fd < 0)
		return (0);
	if (!parse_config(game, fd, &first_map_line))
	{
		if (first_map_line)
			free(first_map_line);
		return (close(fd), 0);
	}
	if (!parse_map_section(game, fd, first_map_line))
		return (close(fd), 0);
	if (!game->map || !game->config)
		return (close(fd), 0);
	if (!validate_map(game, game->map))
		return (close(fd), 0);
	if (!validate_map_boundaries(game->map))
		return (close(fd), 0);
	close(fd);
	return (1);
}
