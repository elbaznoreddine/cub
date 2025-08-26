/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw0_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:06:16 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/24 15:20:44 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	countlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*ptr;
	int				x;
	unsigned int	num;

	x = countlen(n);
	ptr = malloc((x + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	ptr[x] = '\0';
	num = n;
	if (n < 0)
	{
		ptr[0] = '-';
		num = -n;
	}
	while (x > 0)
	{
		if (x == 1 && n < 0)
			break ;
		ptr[x - 1] = (num % 10) + '0';
		num /= 10;
		x--;
	}
	return (ptr);
}

void	anime0(t_list *list, mlx_texture_t	*texture)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < (int)texture->height)
	{
		x = 0;
		while (x < (int)texture->width)
		{
			i = (y * texture->width + x) * 4;
			if (texture->pixels[i + 3] > 0)
				mlx_put_pixel(list->win, x, y, \
				((texture->pixels[i]) << 24) | ((texture->pixels[i + 1]) \
				<< 16) | ((texture->pixels[i + 2]) \
				<< 8) | texture->pixels[i + 3]);
			x++;
		}
		y++;
	}
}

void	anime(void	*param)
{
	t_list			*list;
	static int		j;
	char			*ptr;
	mlx_texture_t	*texture;

	list = param;
	(move0(list), move1(list), move11(list), move2(list), draw_p(list));
	j++;
	ptr = ft_strjoin(ft_strdup("bonus/png/"), ft_itoa(j));
	ptr = ft_strjoin(ptr, ".png");
	texture = mlx_load_png(ptr);
	anime0(list, texture);
	if (j == 40)
		j = 0;
	mlx_delete_texture(texture);
}

int	to_move(t_list *list, double y, double x)
{
	int		i;
	double	px;
	double	py;

	i = 0;
	py = list->py;
	px = list->px;
	while (i < list->mspeed)
	{
		py += y;
		px += x;
		if (is_wall(list, py, px) > 0)
			return (0);
		if (is_wall(list, py + 1, px) > 0)
			return (0);
		if (is_wall(list, py - 1, px) > 0)
			return (0);
		if (is_wall(list, py, px + 1) > 0)
			return (0);
		if (is_wall(list, py, px - 1) > 0)
			return (0);
		i++;
	}
	return (1);
}
