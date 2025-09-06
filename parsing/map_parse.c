/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:07:31 by noel-baz          #+#    #+#             */
/*   Updated: 2025/09/06 10:07:32 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*make_spaces(char *line, int current_length, int max_width)
{
	int	spaces_needed;

	if (current_length < max_width)
	{
		spaces_needed = max_width - current_length;
		while (spaces_needed-- > 0)
			line = ft_strjoin(line, " ");
	}
	return (line);
}

int	store_map_line(t_game *game, char *map_content, int *position,
	int line_index)
{
	int		j;
	char	*line;

	j = 0;
	while (map_content[j + *position] && map_content[j + *position] != '\n')
		j++;
	line = ft_substr(map_content, *position, j);
	if (!line)
		return (0);
	if (j < game->map->width)
		line = make_spaces(line, j, game->map->width);
	game->map->grid[line_index] = line;
	*position += j;
	if (map_content[*position] == '\n')
		(*position)++;
	return (1);
}

int	calculate_map_dimensions(t_game *game, char *map_content, int map_height)
{
	int	i;
	int	j;
	int	k;

	game->map->height = map_height;
	game->map->width = 0;
	i = 0;
	k = 0;
	while (map_content && map_content[i] && k < map_height)
	{
		j = 0;
		while (map_content[j + i] && map_content[j + i] != '\n')
			j++;
		if (j > game->map->width)
			game->map->width = j;
		i += j;
		if (map_content[i] == '\n')
			i++;
		k++;
	}
	return (1);
}

int	fill_map_grid(t_game *game, char *map_content, int map_height)
{
	int	position;
	int	line_index;

	game->map->grid = malloc(sizeof(char *) * (map_height + 1));
	if (!game->map->grid)
		return (0);
	calculate_map_dimensions(game, map_content, map_height);
	(1) && (position = 0, line_index = 0);
	while (map_content && map_content[position] && line_index < map_height)
	{
		if (!store_map_line(game, map_content, &position,
				line_index))
		{
			while (line_index > 0)
			{
				line_index--;
				free(game->map->grid[line_index]);
			}
			free(game->map->grid);
			return (0);
		}
		line_index++;
	}
	game->map->grid[line_index] = NULL;
	return (1);
}

int	read_entire_map_content(t_game *game, int fd, char *first_map_line)
{
	char	*line;
	int		map_height;
	char	*map_content;

	map_height = 1;
	map_content = ft_strdup(first_map_line);
	line = get_next_line(fd);
	while (line)
	{
		if (!line || line[0] == '\0' || line[0] == '\n')
		{
			free(line);
			return (free(map_content), 0);
		}
		map_content = ft_strjoin(map_content, line);
		map_height++;
		free(line);
		line = get_next_line(fd);
	}
	if (!fill_map_grid(game, map_content, map_height))
		return (free(map_content), 0);
	free(map_content);
	return (1);
}
