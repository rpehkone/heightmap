/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/30 18:54:25 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	printer3(t_xyz *start, t_xyz *stop, t_xyz *angle, int x)
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

void	printer2(t_xyz *start, t_xyz *stop, t_xyz *angle, int width)
{
	static int counter = 0;

	stop->x += angle->z;
	stop->y -= angle->z;
	start->y += angle->x;
	stop->y += angle->x;
	start->x += angle->y;
	stop->x += angle->y;
	if (!counter)
		counter = width;
	counter--;
	if (!counter)
		printer3(start, stop, angle, width);
}

void	storage(int call, int *x, int *y)
{
	static int store_x;
	static int store_y;

	if (call)
	{
		store_x = *x;
		store_y = *y;
	}
	else
	{
		 *x = store_x;
		 *y = store_y;
	}
}

void	add_height(t_xyz *start, t_xyz *stop, t_xyz *angle, int call, void **mlx)
{
	static int	**map = NULL;
	static int	swap = 1;
	int a;
	int b;
	int x;
	int y;

	if (!map)
		map = make_map((char *)mlx[2], &a, &b);
	a = 2;
	b = 1;
	swap = swap ? 0 : 1;
	if (call)
	{
		a = 1;
		b = 2;
	}
	storage(0, &x, &y);
	stop->y -= map[y - a][x - b] * angle->z / 10;
	stop->x -= map[y - a][x - b] * angle->z / 10;
	start->y -= map[y - 1][x - 1] * angle->z / 10;
	start->x -= map[y - 1][x - 1] * angle->z / 10;
	print_line(start, stop, mlx, 0xFF0000);
	stop->y += map[y - a][x - b] * angle->z / 10;
	stop->x += map[y - a][x - b] * angle->z / 10;
	start->y += map[y - 1][x - 1] * angle->z / 10;
	start->x += map[y - 1][x - 1] * angle->z / 10;
}

void	ft_printer(void **mlx, t_xyz *angle, t_xyz start, t_xyz stop)
{
	static int	width = 0;
	static int	height = 0;
	int			x;
	int			y;

	if (!width)
	{
		width = get_width(mlx[2]);
		height = get_height(mlx[2]);
	}
	y = height + 1;
	while (--y > 0 && (x = width + 1))
		while (--x > 0)
		{
			storage(1, &x, &y);
			start.x += angle->z;
			stop.x += angle->z;
			if (x > 1)
				add_height(&start, &stop, angle, 1, mlx);
			stop.x -= angle->z;
			stop.y += angle->z;
			if (y > 1)
				add_height(&start, &stop, angle, 0, mlx);
			printer2(&start, &stop, angle, width);
		}
}
