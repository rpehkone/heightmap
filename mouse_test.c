/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/04 17:08:42 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

typedef struct	coord {
		float	x;
		float	y;
		float	z;
}				xyz;

typedef struct	button {
		int x;
		int y;
		int size_x;
		int size_y;
		int	b_color;
		int	bc_color;
		int	t_color;
		int	tc_color;
		char text[20];
}				button;

typedef struct	asdkfasdf {
		int	x;
		int	y;
		int color;
		int charge;
}				particle;

void	ft_putnbr(int n)
{
	char	str[11];
	int		tmp;
	int		size;

	size = 0;
	if (n == 0)
		write(1, "0", 1);
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n < 0)
		if (n *= -1)
			write(1, "-", 1);
	tmp = n;
	while (tmp > 0 && ++size)
		tmp /= 10;
	str[size] = '\0';
	while (size--)
	{
		str[size] = n % 10 + '0';
		n /= 10;
	}
	size++;
	while (str[size])
		write(1, &str[size++], 1);
}

float	ft_abs(float n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

void	print_line(xyz *start, xyz *stop, void **mlx, unsigned color)
{
	xyz	step;
	xyz	pos;

	pos.x = start->x;
	pos.y = start->y;
	/*printf("start->x = %d\n", start->x);
	printf("start->y = %d\n", start->y);
	printf("stop->x = %d\n", stop->x);
	printf("stop->y = %d\n", stop->y);*/
	pos.z = 0;
	step.z = ft_abs(stop->x - start->x) > ft_abs(stop->y - start->y) ?
			ft_abs(stop->x - start->x) : ft_abs(stop->y - start->y);
	step.x = (stop->x - start->x) / (float)step.z;
	step.y = (stop->y - start->y) / (float)step.z;
	while (pos.z <= step.z)
	{
		mlx_pixel_put(mlx[0], mlx[1], pos.x, pos.y, color);
		pos.x += step.x;
		pos.y += step.y;
		pos.z++;
	}
}

void	ft_point(void **mlx, particle p)
{
	mlx_pixel_put(mlx[0], mlx[1], p.x, p.y, p.color);
	mlx_pixel_put(mlx[0], mlx[1], p.x + 1, p.y, p.color);
	mlx_pixel_put(mlx[0], mlx[1], p.x - 1, p.y, p.color);
	mlx_pixel_put(mlx[0], mlx[1], p.x, p.y + 1, p.color);
	mlx_pixel_put(mlx[0], mlx[1], p.x, p.y - 1, p.color);
}

int		slen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	put_button(button *b, void **mlx)
{
	xyz start;
	xyz stop;

	start.x = b->x;
	start.y = b->y;
	stop.x = b->x + b->size_x;
	stop.y = b->y;

	//make fill area function?
	while (start.y < b->y + b->size_y)
	{
		print_line(&start, &stop, mlx, b->b_color);
		start.y++;
		stop.y++;
	}
	mlx_string_put(mlx[0], mlx[1], b->x + b->size_x / 2 - (slen(b->text) / 2 * 9),
			b->y + b->size_y / 2 - 11, b->t_color, b->text);
}

void testf()
{
	printf("on\n");
}

int		handle_button(void **mlx, button b, int x, int y)
{
	if (x > b.x && x < b.x + b.size_x &&
	y > b.y && y < b.y + b.size_y)
	{
		b.b_color = b.bc_color;
		b.t_color = b.tc_color;
		put_button(&b, mlx);
		return (1);
	}
	put_button(&b, mlx);
	return (0);
}
/*
typedef struct	bt {
		int x;
		int y;
		int size_x;
		int size_y;
		int	b_color;
		int	bc_color;
		int	t_color;
		int	tc_color;
		char text[20];
}				button;*/

void	data(int call, int new_x, int new_y, void **mlx)
{
	static button	test = {.x = 0, .y = 950, .size_x = 100, .size_y = 50, .b_color = 0xFF0000,
						.bc_color = 0xFFFFFF, .t_color = 0, .tc_color = 0xFF0000, .text = "TEST"};
	static button	fff = {.x = 40, .y = 50, .size_x = 200, .size_y = 350, .b_color = 0xFF0000,
						.bc_color = 0xFFFFFF, .t_color = 0, .tc_color = 0xFF0000, .text = "asd01021123"};
	static int		x = 0;
	static int		y = 0;

	if (call == 2)
	{
		x = new_x;
		y = new_y;
	}
	if (handle_button(mlx, test, x, y) && call == 1)
		testf();
	if (handle_button(mlx, fff, x, y) && call == 1)
		testf();
}

int		asd(int call, int xd, int yd, void **mlx)
{
	static particle *ptr = NULL;
	static int x = 0;
	static int y = 0;
	static unsigned line_color = 0xFFFFFF;
	int amount = 100;
	int range = 100;

	if (call != 1 || call != 3)
	{
		x = xd;
		y = yd;
	}
	if (!ptr)
	{
		srand(time(0));
		ptr = (particle*)malloc(sizeof(particle) * amount);
		for (int i = 0; i < amount; i++)
		{
			ptr[i].x = rand() % 1000;
			ptr[i].y = rand() % 1000;
			ptr[i].charge = rand() % 2;
			ptr[i].color = 0xFF0000;
		}
	}
	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount; j++)
		{
			if (ptr[j].x > ptr[i].x - range && ptr[j].x < ptr[i].x + range &&
			ptr[j].y > ptr[i].y - range && ptr[j].y < ptr[i].y + range)
			{
				if (ptr[j].x > ptr[i].x)
					ptr[j].x++;
				if (ptr[j].x < ptr[i].x)
					ptr[j].x--;
				if (ptr[j].y > ptr[i].y)
					ptr[j].y++;
				if (ptr[j].y < ptr[i].y)
					ptr[j].y--;
				ptr[i].color = 0xFF0000;
			}
			else
				ptr[i].color = 0x00FF00;
			if (ptr[j].x > ptr[i].x - range + 1 && ptr[j].x < ptr[i].x + range + 1 &&
			ptr[j].y > ptr[i].y - range + 1 && ptr[j].y < ptr[i].y + range + 1)
			{
				xyz start = {.x = ptr[i].x, .y = ptr[i].y};
				xyz stop = {.x = ptr[j].x, .y = ptr[j].y};
				print_line(&start, &stop, mlx, line_color);
			}
			if (i != j && ptr[j].x == ptr[i].x && ptr[j].x == ptr[i].x &&
			ptr[j].y == ptr[i].y && ptr[j].y == ptr[i].y)
			{
				ptr[j].x++;
				ptr[j].y++;
			}
		}
	}
	for (int i = 0; i < amount; i++)
	{
		if (x > ptr[i].x - range && x < ptr[i].x + range &&
		y > ptr[i].y - range && y < ptr[i].y + range)
		{
			if (x > ptr[i].x)
				ptr[i].x += 5;
			if (x < ptr[i].x)
				ptr[i].x -= 5;
			if (y > ptr[i].y)
				ptr[i].y += 5;
			if (y < ptr[i].y)
				ptr[i].y -= 5;
			ptr[i].color = 0xFF0000;
		}
		else
			ptr[i].color = 0x00FF00;
	}
	/*if (x > p2.x - 10 && x < p2.x + 10 &&
	y > p2.y - 10 && y < p2.y + 10)
	{
		if (x < p2.x)
			p2.x++;
		if (x > p2.x)
			p2.x--;
		if (y < p2.y)
			p2.y++;
		if (y > p2.y)
			p2.y--;
		p2.color = 0x00FF00;
	}
	else
		p2.color = 0xFF0000;
	*/
	mlx_clear_window(mlx[0], mlx[1]);
	for (int i = 0; i < amount; i++)
		ft_point(mlx, ptr[i]);
	return (0);
}

int		handle_keyboard(int key, void **mlx)
{
	printf("key = %d\n", key);
	if (key == 53)
		exit (0);
	data(0, 0, 0, mlx);
	return (0);
}

int		handle_mouse(int button, int x, int y, void **mlx)
{
	printf("button = %d\n", button);
	data(1, 0, 0, mlx);
	return (0);
}

int		handle_cursor(int x, int y, void **mlx)
{
	data(2, x, y, mlx);
	return (0);
}

int		handle_loop(void **mlx)
{
	static int i = 0;

	i++;
	if (i < 200)
		return (0);
	i = 0;
	data(3, 0, 0, mlx);
	return (0);
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	**mlx;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "fdf");
	mlx = (void**)malloc(sizeof(void*) * 2);
	mlx[0] = mlx_ptr;
	mlx[1] = win_ptr;
	mlx_hook(win_ptr, 2, 0, handle_keyboard, mlx);
	mlx_hook(win_ptr, 5, 0, handle_mouse, mlx);
	mlx_hook(win_ptr, 6, 0, handle_cursor, mlx);
	mlx_loop_hook(mlx_ptr, handle_loop, mlx);
	mlx_loop(mlx_ptr);
}
