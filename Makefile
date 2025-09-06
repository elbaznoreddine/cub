# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 11:46:20 by yzoullik          #+#    #+#              #
#    Updated: 2025/09/06 13:12:43 by noel-baz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=cub3D
FLAGS= -Werror -Wextra -Wall #-fsanitize=address -g3
MLX_DIR = /mnt/homes/noel-baz/Documents/MLX42
MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit $(MLX_DIR)/build/libmlx42.a  -Iinclude -lglfw -L"/mnt/homes/noel-baz/.brew/opt/glfw/lib"

PARSE= parsing/func_utils/utils_1.c parsing/utils_parse.c parsing/parse_config.c parsing/get_next_line.c \
	   parsing/func_utils/utils_2.c parsing/parse.c parsing/map_parse.c parsing/map_parse1.c \
	   parsing/map_parse2.c parsing/parse_config1.c parsing/parse_config2.c parsing/parse_config3.c \
	   parsing/func_utils/utils_3.c

BPARSE= bonus/parsing_bonus/func_utils/utils_1_bonus.c bonus/parsing_bonus/utils_parse_bonus.c bonus/parsing_bonus/parse_config_bonus.c bonus/parsing_bonus/get_next_line.c \
	    bonus/parsing_bonus/func_utils/utils_2_bonus.c bonus/parsing_bonus/parse_bonus.c bonus/parsing_bonus/map_parse_bonus.c bonus/parsing_bonus/map_parse1_bonus.c \
	    bonus/parsing_bonus/map_parse2_bonus.c bonus/parsing_bonus/parse_config1_bonus.c bonus/parsing_bonus/parse_config2_bonus.c bonus/parsing_bonus/parse_config3_bonus.c \
		bonus/parsing_bonus/func_utils/utils_3_bonus.c

EXEC= cub3d.c\
		draw.c\
		move.c\
		dda.c\
		utils.c\
		3d.c\
		3d_utils.c\

BEXEC = bonus/cub3d_bonus.c\
		bonus/draw_bonus.c\
		bonus/draw0_bonus.c\
		bonus/move_bonus.c\
		bonus/dda_bonus.c\
		bonus/minimap_bonus.c\
		bonus/utils_bonus.c\
		bonus/3d_bonus.c\
		bonus/3d_bonus_utils.c\
		bonus/draw_move_bonus.c

OBJ=$(PARSE:.c=.o) $(EXEC:.c=.o)
BOBJ=$(BPARSE:.c=.o) $(BEXEC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) cub3D.h
	make -C $(MLX_DIR)/build
	cc $(FLAGS) $(MLXFLAGS) $(OBJ) -o $(NAME) 

bonus: $(BOBJ) bonus/cub3D_bonus.h
	make -C $(MLX_DIR)/build
	cc $(FLAGS) $(MLXFLAGS) $(BOBJ) -o $(NAME)_bonus 

%.o:%.c cub3D.h bonus/cub3D_bonus.h
	cc $(FLAGS) $(MFLAGS) -c $< -o $@
clean:
	rm -rf $(OBJ) $(BOBJ)
fclean: clean
	rm -rf $(NAME) $(NAME)_bonus

re: fclean all