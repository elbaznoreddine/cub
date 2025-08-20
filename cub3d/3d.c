/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:38:58 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/19 02:56:42 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t *get_wall_texture(t_list *list, double ray_angle)
{
    double	rayDirX;
    double	rayDirY;
    int		side;

	rayDirX = cos(ray_angle);
	rayDirY = sin(ray_angle);
    if (list->hd < list->vd)
        side = 1;
	else
        side = 0;
    if (side == 1)
	{
        if (rayDirY > 0)
            return list->north_texture;
        else
            return list->south_texture;
    }
	else
	{
        if (rayDirX > 0)
            return list->west_texture;
        else
            return list->east_texture;
	}
}

void	draw_wall_texture(t_list *list, int screen_x, int wall_top,
			int wall_bottom, double ray_angle)
{
	mlx_texture_t	*texture;
	double		wall_x;
	int		tex_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int		side;
	double		offset;
	int		wall_height;
	double		tex_step;
	double		tex_pos;
	int		sy;
	int		ty;
	int		pixel_index;
	uint32_t	color;

	texture = get_wall_texture(list, ray_angle);
	if (!texture || !texture->pixels)
		return ;
	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	if (list->hd < list->vd)
		side = 1;
	else
		side = 0;
	if (side == 1)
		wall_x = list->hwallx;
	else
		wall_x = list->vwally;
	offset = fmod(wall_x, (double)list->tail) / (double)list->tail;
	if (offset < 0)
		offset += 1.0;
	tex_x = (int)(offset * texture->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (int)texture->width)
		tex_x = texture->width - 1;
	if ((side == 0 && ray_dir_x < 0) || (side == 1 && ray_dir_y > 0))
		tex_x = texture->width - tex_x - 1;
	wall_height = wall_bottom - wall_top;
	if (wall_height <= 0)
		return ;
	tex_step = (double)texture->height / wall_height;
	tex_pos = 0.0;
	sy = wall_top;
	while (sy < wall_bottom)
	{
		if (sy >= 0 && sy < list->h)
		{
			ty = (int)tex_pos;
			if (ty < 0)
				ty = 0;
			if (ty >= (int)texture->height)
				ty = texture->height - 1;
			pixel_index = (ty * texture->width + tex_x) * 4;
			color = (texture->pixels[pixel_index] << 24)
				| (texture->pixels[pixel_index + 1] << 16)
				| (texture->pixels[pixel_index + 2] << 8) | 255;
			mlx_put_pixel(list->win, screen_x, sy, color);
		}
		tex_pos += tex_step;
		sy++;
	}
}

void draw_3dwall(t_list *list, int top, int down, int i, double v)
{
    int	z;

    z = 0;
    while (z < list->h / 2)
	{
        mlx_put_pixel(list->win, i, z, get_rgba(200, 200, 200, 255));
        z++;
    }
    while (z < list->h)
	{
        mlx_put_pixel(list->win, i, z, get_rgba(110, 110, 120, 255));
        z++;
    }
    draw_wall_texture(list, i, top, down, v);
}

void draw_3d(t_list *list, double d, double v, int i)
{
    double dp;
    double wh;
    int wsh;
    int top;
    int down;

    d *= cos(v - list->v);
    dp = (list->w / 2) / tan(list->fov / 2);
    wh = (list->tail / d) * dp;
    wsh = (int)wh;
    top = (list->h / 2) - (wsh / 2);
    // if (top < 0)
    //     top = 0;
    down = (list->h / 2) + (wsh / 2);
    // if (down > list->h)
    //     down = list->h;
    draw_3dwall(list, top, down, i, v);
}

void	draw_wall(t_list *list, double v, double i)
{
	double	x;
	double	y;
	double	d;

	x = 0;
	y = 0;
	list->hd = 1000000;
	list->vd = 1000000;
	if (list->hhit)
		list->hd = dis(list, list->hwally, list->hwallx);
	if (list->vhit)
		list->vd = dis(list, list->vwally, list->vwallx);
	if (list->hd < list->vd)
	{
		x = list->hwallx;
		y = list->hwally;
		d = list->hd;
	}
	else
	{
		x = list->vwallx;
		y = list->vwally;
		d = list->vd;
	}
	draw_3d(list, d, v, i);
}

void	draw_p(t_list *list)
{
	double	x;
	double	y;
	double	i;
	double	v;

	i = 0;
	v = list->v - (list->fov / 2);
	while (i < list->w)
	{
		reset_ang(list, &v);
		y = 0;
		x = 0;
		set_var(list);
		if (v > 0 && v < list->pi)
			list->up = 0;
		if ((v > list->pi / 2 && v < 3 * (list->pi / 2)))
			list->left = 1;
		(h_p(list, v, &y, &x), h_dda(list, y, x));
		(v_p(list, v, &y, &x), v_dda(list, y, x));
		draw_wall(list, v, i);
		v += (list->fov / list->w);
		i++;
	}
}
