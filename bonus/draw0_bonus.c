/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw0_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:06:16 by yzoullik          #+#    #+#             */
/*   Updated: 2025/09/07 16:07:34 by noel-baz         ###   ########.fr       */
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
				mlx_put_pixel(list->win, x, y, get_rgba(texture->pixels[i], \
				texture->pixels[i + 1], texture->pixels[i + 2], \
				texture->pixels[i + 3]));
			x++;
		}
		y++;
	}
}

char	*get_img(int j)
{
	char			*ptr;
	char			*ptr1;

	ptr1 = ft_itoa(j);
	if (!ptr1)
		return (0);
	ptr = ft_strjoin(ft_strdup("bonus/png/"), ptr1);
	if (!ptr)
	{
		free(ptr1);
		return (0);
	}
	free(ptr1);
	ptr = ft_strjoin(ptr, ".png");
	if (!ptr)
		return (0);
	return (ptr);
}

void	anime(void	*param)
{
	t_list			*list;
	static int		j;
	char			*ptr;
	mlx_texture_t	*texture;

	ptr = 0;
	list = param;
	(move0(list), move1(list), move11(list), move2(list), draw_p(list));
	j++;
	ptr = get_img(j);
	if (!ptr)
		return ;
	texture = mlx_load_png(ptr);
	free(ptr);
	if (!texture)
		return ;
	anime0(list, texture);
	if (j == 40)
		j = 0;
	mlx_delete_texture(texture);
}
