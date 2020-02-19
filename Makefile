# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 20:09:24 by rpehkone          #+#    #+#              #
#    Updated: 2020/02/19 18:48:46 by rpehkone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
FILES = fdf.c help_text.c printer.c image.c line.c main.c read_map.c handle_hook.c buttons/*.c
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	make re -C libft
	gcc -Wall -Wextra -Werror $(addprefix src/, $(FILES)) libft/libft.a -I includes/ -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean
	make all
