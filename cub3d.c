/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:49:41 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/27 11:25:14 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_list	*list_init(t_game *game)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->tail = 64;
	list->rows = game->map->height;
	list->cols = game->map->width;
	list->line = game->map->grid;
	list->w = 1280;
	list->h = 720;
	list->ww = list->tail * list->cols;
	list->wh = list->tail * list->rows;
	list->mlx = mlx_init(list->w, list->h, "cub3D", true);
	mlx_set_setting(MLX_MAXIMIZED, true);
	list->win = mlx_new_image(list->mlx, list->w, list->h);
	mlx_image_to_window(list->mlx, list->win, 0, 0);
	list->pi = M_PI;
	list->fov = 60 * (list->pi / 180);
	list->v = game->direction;
	list->mspeed = 7;
	list->rspeed = 2 * (list->pi / 180);
	list->vy = sin(list->v);
	list->vx = cos(list->v);
	list->game = game;
	return (list);
}

void	anime(void	*param)
{
	t_list			*list;

	list = param;
	(move0(list), move1(list), move11(list), move2(list), draw_p(list));
}

mlx_texture_t	*load_png_texture(char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		printf("Error: Failed to load texture: %s\n", path);
		return (NULL);
	}
	return (texture);
}

int	load_all_textures(t_list *list)
{
	list->north_texture = load_png_texture(list->game->config->path_north);
	if (!list->north_texture)
		return (0);
	list->south_texture = load_png_texture(list->game->config->path_south);
	if (!list->south_texture)
		return (0);
	list->east_texture = load_png_texture(list->game->config->path_east);
	if (!list->east_texture)
		return (0);
	list->west_texture = load_png_texture(list->game->config->path_west);
	if (!list->west_texture)
		return (0);
	return (1);
}

int	logic(t_list *list, t_game *game)
{
	list = list_init(game);
	list->f = 1;
	if (!load_all_textures(list))
		return (0);
	draw_p0(list);
	mlx_key_hook(list->mlx, &move, list);
	mlx_loop_hook(list->mlx, &anime, list);
	mlx_loop(list->mlx);
	mlx_terminate(list->mlx);
	return (1);
}

int	main(int ac, char **av)
{
	t_list	*list;
	t_game	*game;

	list = NULL;
	game = NULL;
	if (ac != 2)
		return (write(2, "Error\n./cub3D /path/map.cub\n", 29), 1);
	if (!ft_check_map_extension(av[1]))
		return (write(2, "Error\nThe extention must be .cub\n", 34), 1);
	if (!init_game(&game))
		return (write(2, "Error\ncan't alocate memory\n", 28), 1);
	if (!parse_complete_map_file(game, av[1]))
	{
		free_game(game);
		return (write(2, "Error\nThe config or Map not valid\n", 35), 1);
	}
	if (!logic(list, game))
		write(2, "Error\ntextures can't load\n", 27);
	free_game(game);
	return (0);
}
