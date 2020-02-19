# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 20:09:24 by rpehkone          #+#    #+#              #
#    Updated: 2020/02/19 20:58:48 by rpehkone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
FILES = fdf.c help_text.c printer.c image.c line.c main.c read_map.c handle_hook.c buttons.c buttons_main.c button_2_cycle.c button_3_height.c button_3_slider.c colors.c
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	make re -C libft
	gcc -Wall -Wextra -Werror $(addprefix src/, $(FILES)) libft/libft.a -I src/ -I libft/ -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit -o $(NAME)

clean:
	make clean -C libft

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean
	make all
