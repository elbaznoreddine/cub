/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config1_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:06:29 by noel-baz          #+#    #+#             */
/*   Updated: 2025/09/06 10:06:30 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	store_north_texture(char *texture_path, t_config *config)
{
	if (can_open_texture_file(texture_path))
		return (0);
	config->path_north = texture_path;
	return (1);
}

int	store_south_texture(char *texture_path, t_config *config)
{
	if (can_open_texture_file(texture_path))
		return (0);
	config->path_south = texture_path;
	return (1);
}

int	store_west_texture(char *texture_path, t_config *config)
{
	if (can_open_texture_file(texture_path))
		return (0);
	config->path_west = texture_path;
	return (1);
}

int	store_east_texture(char *texture_path, t_config *config)
{
	if (can_open_texture_file(texture_path))
		return (0);
	config->path_east = texture_path;
	return (1);
}

int	save_config_element(char *element_value, int element_type,
	t_config *config, t_game *game)
{
	if (element_type == 1)
		return (store_north_texture(element_value, config));
	else if (element_type == 2)
		return (store_south_texture(element_value, config));
	else if (element_type == 3)
		return (store_west_texture(element_value, config));
	else if (element_type == 4)
		return (store_east_texture(element_value, config));
	else if (element_type == 5)
		return (store_floor_color(game, element_value, config));
	else if (element_type == 6)
		return (store_ceiling_color(game, element_value, config));
	return (0);
}
