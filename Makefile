all:
	gcc fdf.c main.c get_next_line.c read_map.c -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit -o fdf
	./fdf 42.fdf
test:
	gcc mouse_test.c -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit
