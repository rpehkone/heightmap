# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 20:09:24 by rpehkone          #+#    #+#              #
#    Updated: 2020/02/14 15:03:16 by rpehkone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
FILES = fdf.c help_text.c printer.c image.c main.c read_map.c handle_hook.c buttons/*.c libft/libft.a
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	make re -C libft
	gcc -Wall -Wextra -Werror $(FILES) -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all
