/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:46:43 by yzoullik          #+#    #+#             */
/*   Updated: 2025/08/19 02:55:55 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "/mnt/homes/noel-baz/Documents/MLX42/include/MLX42/MLX42.h"
# include <math.h>

# define BUFFER_SIZE 42

typedef struct s_list
{
	void		*mlx;
	mlx_image_t	*win;
	double		tail;
	double		rows;
	double		cols;
	char		**line;
	double		ww;
	double		wh;
	double		px;
	double		py;
	double		fov;
	double		mspeed;
	double		rspeed;
	double		pi;
	double		v;
	double		vy;
	double		vx;
	int			up;
	int			left;
	double		xstep;
	double		ystep;
	double		vd;
	double		hd;
	int			vhit;
	int			hhit;
	double		vwally;
	double		vwallx;
	double		hwally;
	double		hwallx;
	double		f;
	double		w;
	double		mouse_sens;
	double		last_mouse_x;
	double		h;

	mlx_texture_t *north_texture;
    mlx_texture_t *south_texture;
    mlx_texture_t *east_texture;
    mlx_texture_t *west_texture;
    int tex_width;
    int tex_height;
}				t_list;

char	*get_next_line(int fd);
size_t	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
int		ft_strchr(char *s, int c);
char	*ft_strdup(char *s1);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s);
void	ft_free(char **ptr);

int		parsmap(char *ptr);
void	move(mlx_key_data_t keydata, void	*param);
int		move0(t_list *list);
int		move1(t_list *list);
int		move11(t_list *list);
int		move2(t_list *list);
void	draw_map(t_list *list);

void	draw_1(int x, int y, t_list *list);
void	draw_0(int x, int y, t_list *list);
void	draw_line(t_list *list, double wally, double wallx, double v);
void	draw_cir(t_list *list);

void	draw_map0(t_list *list);
void	draw_line0(t_list *list, double y, double x);

void	draw_p(t_list *list);
void	draw_map(t_list *list);
void	draw_map1(t_list *list);
int		is_wall(t_list *list, double y, double x);

void	h_dda(t_list *list, double nexty, double nextx);
void	v_dda(t_list *list, double nexty, double nextx);
void	h_p(t_list *list, double v, double *y, double *x);
void	v_p(t_list *list, double v, double *y, double *x);

int		get_rgba(int r, int g, int b, int a);
double	dis(t_list *list, double y, double x);
void	ft_free(char **ptr);

void	set_var(t_list *list);
void	reset_ang(t_list *list, double *v);

int load_textures(t_list *list);
void mouse(double xpos, double ypos, void *param);
#endif