/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:10:09 by noel-baz          #+#    #+#             */
/*   Updated: 2025/09/09 10:04:12 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	calculate_wall_position(t_list *list,
							double *wall_x, int *side)
{
	if (list->hd < list->vd)
		*side = 1;
	else
		*side = 0;
	if (*side == 1)
		*wall_x = list->hwallx;
	else
		*wall_x = list->vwally;
}

static int	calculate_texture_x(mlx_texture_t *texture, double wall_x,
							t_list *list)
{
	double	offset;
	int		tex_x;

	offset = fmod(wall_x, (double)list->tail) / (double)list->tail;
	tex_x = (int)(offset * texture->width);
	return (tex_x);
}

static uint32_t	get_pixel_color(mlx_texture_t *texture, int tex_x, int ty)
{
	int			pixel_index;
	uint32_t	color;

	if (ty >= (int)texture->height)
		ty = texture->height - 1;
	pixel_index = (ty * texture->width + tex_x) * 4;
	color = (texture->pixels[pixel_index] << 24)
		| (texture->pixels[pixel_index + 1] << 16)
		| (texture->pixels[pixel_index + 2] << 8) | 255;
	return (color);
}

static void	render_wall_column(t_list *list, mlx_texture_t *texture,
							int screen_x, int tex_x)
{
	int		wall_height;
	double	tex_step;
	double	tex_pos;
	int		sy;

	wall_height = list->down - list->top;
	tex_step = (double)texture->height / wall_height;
	tex_pos = 0.0;
	sy = list->top;
	while (sy < list->down)
	{
		if (sy >= 0 && sy < list->h)
		{
			mlx_put_pixel(list->win, screen_x, sy,
				get_pixel_color(texture, tex_x, (int)tex_pos));
		}
		tex_pos += tex_step;
		sy++;
	}
}

void	draw_wall_texture(t_list *list, int screen_x, double ray_angle)
{
	mlx_texture_t	*texture;
	double			wall_x;
	int				tex_x;
	int				side;

	texture = get_wall_texture(list, ray_angle);
	if (!texture || !texture->pixels)
		return ;
	calculate_wall_position(list, &wall_x, &side);
	list->ray_angle = ray_angle;
	tex_x = calculate_texture_x(texture, wall_x, list);
	render_wall_column(list, texture, screen_x, tex_x);
}
