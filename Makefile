# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artmende <artmende@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/12 15:28:58 by artmende          #+#    #+#              #
#    Updated: 2021/06/02 10:59:43 by artmende         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	OS_RULE = rule_linux
else 
ifeq ($(UNAME_S),Darwin)
	OS_RULE = rule_macos
else
	OS_RULE = rule_else
endif
endif

CC = clang

CFLAGS = -Wall -Wextra -Werror

INCLUDE = -I cub3d_src/includes

SUFFIX = -lbsd -lmlx -lXext -lX11 -lm

SRCS =	./cub3d_src/main.c \
		./cub3d_src/draw_shapes/put_square_circle.c \
		./cub3d_src/draw_shapes/put_line.c \
		./cub3d_src/cast_rays/cast_ray.c \
		./cub3d_src/cast_rays/handling_sprites.c \
		./cub3d_src/hooks_and_pos_update/ft_hooks.c \
		./cub3d_src/hooks_and_pos_update/select_key_action.c \
		./cub3d_src/hooks_and_pos_update/update_pos.c \
		./cub3d_src/initialize_window_and_mlx/initialize_window_and_mlx.c \
		./cub3d_src/display_to_window/minimap.c \
		./cub3d_src/display_to_window/render_sprites.c \
		./cub3d_src/display_to_window/build_frame.c \
		./cub3d_src/display_to_window/render_walls_sprites.c \
		./cub3d_src/utils/from_libft_mem_str.c \
		./cub3d_src/utils/from_libft_nbr.c \
		./cub3d_src/utils/various_utils.c \
		./cub3d_src/read_cub_file_and_build_map/get_data_about_map.c \
		./cub3d_src/read_cub_file_and_build_map/match_line_w_list.c \
		./cub3d_src/read_cub_file_and_build_map/parse_params_lines.c \
		./cub3d_src/read_cub_file_and_build_map/check_map.c \
		./cub3d_src/read_cub_file_and_build_map/verify_map_is_closed.c \
		./cub3d_src/read_cub_file_and_build_map/manage_param_list.c \
		./cub3d_src/read_cub_file_and_build_map/get_map.c \
		./cub3d_src/read_cub_file_and_build_map/check_cub_params.c \
		./cub3d_src/create_bmp_screenshot/create_bmp_screenshot.c \
		./cub3d_src/get_next_line/get_next_line.c \
		./cub3d_src/get_next_line/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

RM = rm -f

NAME = cub3D

LIBMLXA = /usr/local/lib/libmlx.a

MLXH = /usr/local/include/mlx.h

all: $(OS_RULE)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(SUFFIX)


$(LIBMLXA):
	@echo 'Compiling on Linux...'
	cd minilibx-linux && make
	sudo apt install libxext-dev
	sudo apt install libxrandr-dev
	sudo apt install libx11-dev
	sudo apt install libbsd-dev
	sudo apt install libssl-dev
	cd minilibx-linux && sudo cp libmlx.a /usr/local/lib/
	cd minilibx-linux && sudo cp mlx.h /usr/local/include/

$(MLXH):
	@echo 'Compiling on Linux...'
	cd minilibx-linux && make
	sudo apt install libxext-dev
	sudo apt install libxrandr-dev
	sudo apt install libx11-dev
	sudo apt install libbsd-dev
	sudo apt install libssl-dev
	cd minilibx-linux && sudo cp libmlx.a /usr/local/lib/
	cd minilibx-linux && sudo cp mlx.h /usr/local/include/

rule_linux: $(MLXH) $(LIBMLXA) $(NAME)

rule_macos:
	@echo 'This project currently only works on linux...'
#
#	down there is the way to compile on Mac.
#	gcc -Wall -Wextra -Werror *.c -l mlx -framework OpenGL -framework AppKit
#
#	How to make it work on mac : get minilibx for mac.
#	mlx_get_screen_size doesn't work on Mac, so should either make it work
#	somehow, or deactivate it in function "check_correct_resolution" and make
#	sure resolution in cub file is acceptable for the screen.
#
#	keyboard key IDs on mac are different than on Linux, so should adapt them in
#	function "select_key_action".

rule_else:
	@echo 'This project only works on MacOs or Linux.'

clean:
	$(RM) $(OBJS)
	cd minilibx-linux && make clean

fclean: clean
	$(RM) $(NAME)

re: fclean all

cub1: all
	./cub3D ./files/cub/maptest1.cub

cub1_save: all
	./cub3D ./files/cub/maptest1.cub --save

cub2: all
	./cub3D ./files/cub/maptest2.cub

cub2_save: all
	./cub3D ./files/cub/maptest2.cub --save

cub3: all
	./cub3D ./files/cub/maptest3.cub

cub3_save: all
	./cub3D ./files/cub/maptest3.cub --save

recub1: re cub1

.PHONY: clean fclean re all rule_linux rule_macos rule_else cub1 cub2 cub3 cub1_save cub2_save cub3_save recub1
