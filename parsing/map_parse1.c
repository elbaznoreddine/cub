#include "../cub3D.h"

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

int	is_valid_map_character(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != ' ')
		return (0);
	return (1);
}

int	count_player(t_game *game, t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (!is_valid_map_character(map->grid[i][j]))
				return (-1);
			if (is_player_character(map->grid[i][j]))
			{
				set_player_facing_direction(game, map->grid[i][j]);
				game->map->player_x = j;
				game->map->player_y = i;
				player_count++;
			}
			j++;
		}
		i++;
	}
	return (player_count);
}
