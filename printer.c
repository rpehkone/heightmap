/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/28 16:47:39 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	help_rotate(xyz *start, xyz *stop, xyz *angle, int x)
{
	start->x += angle->y;
	stop->x += angle->y;
	start->y += angle->z;
	stop->y += angle->z;
	start->y -= angle->x * (x - 1);
	stop->y -= angle->x * (x - 1);
	start->x -= angle->y * x;
	stop->x -= angle->y * x;
	while (x > 0)
	{
		start->x -= angle->z;
		stop->x -= angle->z;
		x--;
	}
}

void	help_rotate2(xyz *start, xyz *stop, xyz *angle)
{
	stop->x += angle->z;
	stop->y -= angle->z;
	start->y += angle->x;
	stop->y += angle->x;
	start->x += angle->y;
	stop->x += angle->y;
}

//remove start and stop by returning double
void	add_height(int **map, xyz *start, xyz *stop, xyz *angle, int call, int cpy, int y)
{
	int a;
	int b;

	a = 2;
	b = 1;
	if (call)
	{
		a = 1;
		b = 2;
	}
	stop->y -= map[y - a][cpy - b] * angle->z / 10;
	stop->x -= map[y - a][cpy - b] * angle->z / 10;
	start->y -= map[y - 1][cpy - 1] * angle->z / 10;
	start->x -= map[y - 1][cpy - 1] * angle->z / 10;
}

//remove start and stop by returning double
void	remove_height(int **map, xyz *start, xyz *stop, xyz *angle, int call, int cpy, int y)
{
	int a;
	int b;

	a = 2;
	b = 1;
	if (call)
	{
		a = 1;
		b = 2;
	}
	stop->y += map[y - a][cpy - b] * angle->z / 10;
	stop->x += map[y - a][cpy - b] * angle->z / 10;
	start->y += map[y - 1][cpy - 1] * angle->z / 10;
	start->x += map[y - 1][cpy - 1] * angle->z / 10;
}


void	ft_printer(void **mlx, xyz *angle, int offset_x, int offset_y)
{
	static int **map = NULL;
	static int width;
	static int height;
	xyz start = {.x = 0, .y = 0};
	xyz stop = {.x = angle->z + angle->y, .y = angle->x};
	int cpy;

	if (!map)
		map = make_map((char *)mlx[2], &width, &height);
	int y = height;
	start.x += offset_x;
	start.y += offset_y;
	stop.x += offset_x;
	stop.y += offset_y;
	while (y > 0)
	{
		cpy = width;
		while (cpy > 0)
		{
			start.x += angle->z;
			stop.x += angle->z;
			if (cpy > 1)
			{
				add_height(map, &start, &stop, angle, 1, cpy, y);
				print_line(&start, &stop, mlx, 0xFF0000);
				remove_height(map, &start, &stop, angle, 1, cpy, y);
			}
			stop.x -= angle->z;
			stop.y += angle->z;
			if (y > 1)
			{
				add_height(map, &start, &stop, angle, 0, cpy, y);
				print_line(&start, &stop, mlx, 0xFF0000);
				remove_height(map, &start, &stop, angle, 0, cpy, y);
			}
			help_rotate2(&start, &stop, angle);
			cpy--;
		}
		help_rotate(&start, &stop, angle, width);
		y--;
	}
}
