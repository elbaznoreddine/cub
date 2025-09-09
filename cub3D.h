/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 11:46:43 by yzoullik          #+#    #+#             */
/*   Updated: 2025/09/09 10:05:39 by noel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include "/mnt/homes/yzoullik/Documents/MLX42/include/MLX42/MLX42.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_config
{
	char	*floor;
	char	*ceil;
	char	*path_north;
	char	*path_south;
	char	*path_east;
	char	*path_west;
}				t_config;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}				t_map;

typedef struct s_game
{
	double			direction;
	unsigned int	ceil;
	unsigned int	floor;
	t_map			*map;
	t_config		*config;
}					t_game;

typedef struct s_list
{
	void			*mlx;
	mlx_image_t		*win;
	double			tail;
	double			rows;
	double			cols;
	char			**line;
	double			ww;
	double			wh;
	double			px;
	double			py;
	double			fov;
	double			mspeed;
	double			rspeed;
	double			pi;
	double			v;
	double			vy;
	double			vx;
	int				up;
	int				left;
	double			xstep;
	double			ystep;
	double			vd;
	double			hd;
	int				vhit;
	int				hhit;
	double			vwally;
	double			vwallx;
	double			hwally;
	double			hwallx;
	double			f;
	double			w;
	double			h;
	int				top;
	int				down;
	double			ray_angle;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*west_texture;
	t_game			*game;
}				t_list;

char			*get_next_line(int fd);
size_t			ft_strlcpy(char *dst, char *src, size_t dstsize);
char			*ft_strdup(char *s1);
size_t			ft_strlcat(char *dst, char *src, size_t dstsize);
char			*ft_strjoin(char *s1, char *s2);
void			ft_free(char **ptr);
int				parsmap(char *ptr);
void			move(mlx_key_data_t keydata, void	*param);
int				move0(t_list *list);
int				move1(t_list *list);
int				move11(t_list *list);
int				move2(t_list *list);
void			draw_p0(t_list *list);
void			draw_p(t_list *list);
int				to_move(t_list *list, double y, double x);
void			anime(void	*param);
void			draw_p(t_list *list);
int				is_wall(t_list *list, double y, double x);
void			h_dda(t_list *list, double nexty, double nextx);
void			v_dda(t_list *list, double nexty, double nextx);
void			h_p(t_list *list, double v, double *y, double *x);
void			v_p(t_list *list, double v, double *y, double *x);
int				get_rgba(int r, int g, int b, int a);
double			dis(t_list *list, double y, double x);
void			ft_free(char **ptr);
void			set_var(t_list *list);
void			reset_ang(t_list *list, double *v);
void			clean_close(t_list *list);
void			close_window(void	*param);
void			draw_wall_texture(t_list *list, int screen_x, double ray_angle);
mlx_texture_t	*get_wall_texture(t_list *list, double ray_angle);
size_t			ft_strlen(const char *str);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_substr(char *s, unsigned int index, size_t bytes);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(char *s);
int				ft_check_map_extension(char *exten);
int				init_game(t_game **game);
int				parse_complete_map_file(t_game *game, char *map_filename);
char			*get_next_line(int fd);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			free_game(t_game *game);
void			free_config(t_config *config);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			**ft_split(char const *s, char c);
void			free_split(char **split);
int				ft_atoi(const char *str);
void			print_all_map(t_game *game);
int				setup_empty_config(t_config *config);
int				process_config_line(t_game *game, char *line, int *element_type,
					char **first_map_line);
int				check_config_completeness(t_config *config);
int				config_type(char *line, int i, int j);
int				read_entire_map_content(t_game *game, int fd,
					char *first_map_line);
int				count_player(t_game *game, t_map *map);
int				is_border_position(int i, int j, t_map *map);
int				has_invalid_border_character(char c);
int				space_touches_empty_cell(t_map *map, int i, int j);
int				store_floor_color(t_game *game, char *color_string,
					t_config *config);
int				store_ceiling_color(t_game *game, char *color_string,
					t_config *config);
int				are_rgb_values_valid(char **rgb_array);
char			*extract_file_path(char *line);
int				config_element_already_exists(t_config *config,
					int element_type);
int				save_config_element(char *element_value, int element_type,
					t_config *config, t_game *game);
int				can_open_texture_file(char *file_path);

#endif