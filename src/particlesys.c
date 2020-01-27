/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/09 20:43:32 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		particlesys(int call, int x, int y, void **mlx)
{
	static particle *ptr = NULL;
	static unsigned line_color = 0xFFFFFF;
	int amount = 100;
	int range = 100;

	if (call == 1)
		line_color = rand() % 0xFFFFFF;
	else if (call == 2)
		line_color = 0;
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

void	data(int call, int new_x, int new_y, void **mlx)
{
	static button	b1 = {.x = 0, .y = 950, .size_x = 100, .size_y = 50, .b_color = 0xFF0000,
						.bc_color = 0xFFFFFF, .t_color = 0, .tc_color = 0xFF0000, .type = 0, .text = "TEST"};
	static button	b2 = {.x = 40, .y = 50, .size_x = 200, .size_y = 350, .b_color = 0xFF0000,
						.bc_color = 0xFFFFFF, .t_color = 0, .tc_color = 0xFF0000, .type = 0, .text = "asd01021123"};
	static button	b3 = {.x = 400, .y = 200, .size_x = 20, .size_y = 20, .b_color = 0x00FF00,
						.bc_color = 0xFF00FF, .t_color = 0, .tc_color = 0xF00F00, .type = 1, .text = "asd"};
	static int		x = 0;
	static int		y = 0;
	static int		what = 1;

	if (call ==  6)
	{
		x = new_x;
		y = new_y;
	}
	if (what == 0)
	{
		particlesys(0, x, y, mlx);
		if (handle_button(mlx, b1, x, y) && call == 4)
			particlesys(1, x, y, mlx);
		if (handle_button(mlx, b2, x, y) && call == 4)
			particlesys(2, x, y, mlx);
		if (handle_button(mlx, b3, x, y) && call == 4)
			what = 1;
	}
	else
		if (call == 6)
			matrix(call, new_x, new_y, mlx);
		else
			matrix(-1, 0, 0, mlx);
}
