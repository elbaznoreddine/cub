/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 10:06:34 by noel-baz          #+#    #+#             */
/*   Updated: 2025/09/06 10:38:49 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	store_color(t_game *game, char **rgb_array, int color_type)
{
	if (color_type == 5)
	{
		game->floor = (ft_atoi(rgb_array[0]) << 24)
			| (ft_atoi(rgb_array[1]) << 16)
			| (ft_atoi(rgb_array[2]) << 8) | 255;
	}
	else if (color_type == 6)
	{
		game->ceil = (ft_atoi(rgb_array[0]) << 24)
			| (ft_atoi(rgb_array[1]) << 16)
			| (ft_atoi(rgb_array[2]) << 8) | 255;
	}
}

int	valid_commas(char *color_string)
{
	int	i;

	i = 0;
	if (color_string[0] == ',')
		return (1);
	while (color_string[i])
	{
		if (color_string[i] && color_string[i] == ','
			&& color_string[i + 1] == ',')
			return (1);
		i++;
	}
	if (color_string[i - 1] == ',')
		return (1);
	return (0);
}

int	validate_color(t_game *game, char *color_string, int color_type)
{
	char	**rgb_array;

	if (valid_commas(color_string))
		return (1);
	rgb_array = ft_split(color_string, ',');
	if (!rgb_array)
		return (1);
	if (are_rgb_values_valid(rgb_array))
		return (free_split(rgb_array), 1);
	store_color(game, rgb_array, color_type);
	return (free_split(rgb_array), 0);
}

int	store_floor_color(t_game *game, char *color_string, t_config *config)
{
	if (validate_color(game, color_string, 5))
		return (0);
	config->floor = color_string;
	return (1);
}

int	store_ceiling_color(t_game *game, char *color_string, t_config *config)
{
	if (validate_color(game, color_string, 6))
		return (0);
	config->ceil = color_string;
	return (1);
}
