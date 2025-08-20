/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:49:41 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/19 02:58:10 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsmap(char *ptr)
{
	int		len;
	int		i;
	char	*ex;

	len = ft_strlen(ptr) - 1;
	ex = ".cub";
	i = 3;
	if (len > 3)
	{
		while (i >= 0)
		{
			if (ptr[len--] != ex[i--])
				return (0);
		}
		return (1);
	}
	return (0);
}

t_list	*list_init(char **ptr)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->tail = 64;
	list->rows = 20;
	list->cols = 17;
	list->line = ft_split(*ptr);
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
	list->v = 3 * list->pi / 2;
	list->mspeed = 7;
	list->rspeed = 2 * (list->pi / 180);
	list->vy = sin(list->v);
	list->vx = cos(list->v);
	return (list);
}

int	is_wall(t_list *list, double y, double x)
{
	double	j;
	double	i;

	if (x < 0 || x > list->ww || y < 0 || y > list->wh)
		return (1);
	j = floor(y / list->tail);
	i = floor(x / list->tail);
	if (list->line[(int) j][(int) i] == '1')
		return (1);
	return (0);
}

void	anime(void	*param)
{
	t_list			*list;

	list = param;
	(move0(list), move1(list), move11(list), move2(list), draw_p(list));
}

mlx_texture_t *load_png_texture(char *path)
{
    mlx_texture_t *texture;
    
    texture = mlx_load_png(path);
    if (!texture)
    {
        printf("Error: Failed to load texture: %s\n", path);
        return (NULL);
    }
    
    printf("Loaded texture: %s (%dx%d)\n", path, texture->width, texture->height);
    return (texture);
}

int load_all_textures(t_list *list)
{
    list->north_texture = load_png_texture("textures/n.png");
    if (!list->north_texture)
        return (0);
    list->south_texture = load_png_texture("textures/s.png");
    if (!list->south_texture)
        return (0);
    list->east_texture = load_png_texture("textures/e.png");
    if (!list->east_texture)
        return (0);
    list->west_texture = load_png_texture("textures/w.png");
    if (!list->west_texture)
        return (0);
    list->tex_width = list->north_texture->width;
    list->tex_height = list->north_texture->height;
    printf("All textures loaded successfully!\n");
    return (1);
}

int	logic(t_list *list, char **str)
{
	list = list_init(str);
	list->f = 1;
	load_all_textures(list);
	draw_p0(list);
	mlx_key_hook(list->mlx, &move, list);
	mlx_loop_hook(list->mlx, &anime, list);
	mlx_loop(list->mlx);
	mlx_terminate(list->mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_list	*list;
	char	*str;
	char	*ptr;
	int		fd;

	list = 0;
	if (ac != 2 || !parsmap(av[1]))
		return (0);
	str = 0;
	ptr = 0;
	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
		return (0);
	ptr = get_next_line(fd);
	if (!ptr || ptr[0] == '\n')
		return (close(fd), free(ptr), get_next_line(-10), 0);
	while (ptr)
	{
		str = ft_strjoin(str, ptr);
		free(ptr);
		ptr = get_next_line(fd);
		if (!str || (ptr && str[ft_strlen(str) - 1] == '\n' && ptr[0] == '\n'))
			return (close(fd), free(str), free(ptr), get_next_line(-10), 0);
	}
	return (close(fd), logic(list, &str));
}
