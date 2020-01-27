all:
	gcc fdf.c printer.c main.c get_next_line.c read_map.c -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit -o fdf
	./fdf 42.fdf
