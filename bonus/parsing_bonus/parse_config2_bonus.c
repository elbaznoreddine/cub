/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:06:32 by noel-baz          #+#    #+#             */
/*   Updated: 2025/09/06 10:40:12 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	can_open_texture_file(char *file_path)
{
	int	fd;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

int	are_rgb_values_valid(char **rgb_array)
{
	int	i;

	i = 0;
	while (rgb_array[i])
	{
		if (ft_atoi(rgb_array[i]) == -1)
			return (1);
		i++;
	}
	if (i > 3 || i < 3)
		return (1);
	return (0);
}

char	*extract_file_path(char *line)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*path;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ' )
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	start = i;
	while (line[i] && line[i] != '\n')
		i++;
	end = i;
	while (end > start && line[end - 1] == ' ')
		end--;
	if (start >= end)
		return (NULL);
	path = malloc(end - start + 1);
	if (!path)
		return (NULL);
	ft_strncpy(path, line + start, (end - start) + 1);
	return (path[end - start] = '\0', path);
}

int	config_element_already_exists(t_config *config, int element_type)
{
	if (element_type == 1 && config->path_north)
		return (1);
	if (element_type == 2 && config->path_south)
		return (1);
	if (element_type == 3 && config->path_west)
		return (1);
	if (element_type == 4 && config->path_east)
		return (1);
	if (element_type == 5 && config->floor)
		return (1);
	if (element_type == 6 && config->ceil)
		return (1);
	return (0);
}
