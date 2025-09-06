/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:07:41 by noel-baz          #+#    #+#             */
/*   Updated: 2025/09/06 10:30:59 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_valid_config_character(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == 'F' || c == 'C')
		return (1);
	return (0);
}

int	identify_config_type(char *line)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!is_valid_config_character(line[i]))
		return (0);
	k = i;
	if (line[i] != '\0')
	{
		while (line[k] && line[k] != ' ')
		{
			j++;
			k++;
		}
		return (config_type(line, i, j));
	}
	return (-1);
}

int	setup_empty_config(t_config *config)
{
	config->path_north = NULL;
	config->path_south = NULL;
	config->path_west = NULL;
	config->path_east = NULL;
	config->floor = NULL;
	config->ceil = NULL;
	return (1);
}

int	check_config_completeness(t_config *config)
{
	if (!config->path_north || !config->path_south
		|| !config->path_west || !config->path_east
		|| !config->floor || !config->ceil)
		return (0);
	return (1);
}

int	process_config_line(t_game *game, char *line, int *element_type,
	char **first_map_line)
{
	char	*element_value;

	*element_type = identify_config_type(line);
	if (*element_type == -1)
		return (0);
	if (*element_type == 0)
	{
		*first_map_line = line;
		return (1);
	}
	if (config_element_already_exists(game->config, *element_type))
		return (0);
	element_value = extract_file_path(line);
	if (!element_value)
		return (0);
	if (!save_config_element(element_value, *element_type, game->config, game))
	{
		free(element_value);
		return (0);
	}
	return (2);
}
