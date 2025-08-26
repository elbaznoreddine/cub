#include "../cub3D.h"

int	space_touches_empty_cell(t_map *map, int i, int j)
{
	if (map->grid[i][j] == ' ')
	{
		if ((j < map->width - 1 && map->grid[i][j + 1] == '0') ||
			(j > 0 && map->grid[i][j - 1] == '0') ||
			(i < map->height - 1 && map->grid[i + 1][j] == '0') ||
			(i > 0 && map->grid[i - 1][j] == '0'))
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
