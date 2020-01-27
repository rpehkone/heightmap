all:
	rm -rf a.out
	gcc math.c buttons.c fdf.h 3d.c helpf.c main.c particlesys.c -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit
	./a.out

colors:
	rm -rf a.out
	gcc main.c colors.c -I /usr/local/include -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit
	./a.out
