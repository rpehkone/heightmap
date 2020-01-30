# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/30 20:09:24 by rpehkone          #+#    #+#              #
#    Updated: 2020/01/30 20:12:26 by rpehkone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
FILES = fdf.c printer.c main.c get_next_line.c read_map.c
.PHONY: clean fclean re all

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror $(FILES) -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all
