# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: noel-baz <noel-baz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/05 11:46:20 by yzoullik          #+#    #+#              #
#    Updated: 2025/08/14 02:14:13 by noel-baz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
HEADER = cub3d.h

SRC =	cub3d.c\
		get_next_line.c\
		get_next_line_utils.c\
		split.c\
		draw.c\
		move.c\
		dda.c\
		utils.c\
		3d.c\


NAMEB = cub3d_bonus
HEADERB = bonus/cub3d_bonus.h

SRCB =	bonus/cub3d_bonus.c\
		bonus/get_next_line_bonus.c\
		bonus/get_next_line_utils_bonus.c\
		bonus/split_bonus.c\
		bonus/draw_bonus.c\
		bonus/draw0_bonus.c\
		bonus/move_bonus.c\
		bonus/dda_bonus.c\
		bonus/minimap_bonus.c\
		bonus/utils_bonus.c\
		bonus/3d_bonus.c\
		
OBJ = $(SRC:.c=.o)
OBJB = $(SRCB:.c=.o)

MLX_DIR = /mnt/homes/noel-baz/Documents/MLX42

CFLAGS = -Wall -Wextra -Werror # -g3 -fsanitize=address

# MLXFLAGS = MLX42/build/libmlx42.a  -Iinclude -ldl -lglfw -pthread -lmws
MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit $(MLX_DIR)/build/libmlx42.a  -Iinclude -lglfw -L"/mnt/homes/noel-baz/.brew/opt/glfw/lib"

all: $(NAME)

bonus : $(NAMEB)

$(NAME): $(OBJ)
	cc $(CFLAGS)  $(OBJ) -o $(NAME) $(MLXFLAGS)

$(NAMEB): $(OBJB)
	cc $(CFLAGS) $(OBJB) -o $(NAMEB) $(MLXFLAGS)

%.o: %.c $(HEADER)
	cc $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c $(HEADERB)
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJB)

fclean: clean
	rm -f $(NAME) $(NAMEB)

re: fclean all

.PHONY: clean
