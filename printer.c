/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/28 17:45:32 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	printer3(xyz *start, xyz *stop, xyz *angle, int x)
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

void	printer2(xyz *start, xyz *stop, xyz *angle)
{
	stop->x += angle->z;
	stop->y -= angle->z;
	start->y += angle->x;
	stop->y += angle->x;
	start->x += angle->y;
	stop->x += angle->y;
}

//remove start and stop by returning double
void	add_height(int **map, xyz *start, xyz *stop, xyz *angle, int call, int x, int y)
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
	stop->y -= map[y - a][x - b] * angle->z / 10;
	stop->x -= map[y - a][x - b] * angle->z / 10;
	start->y -= map[y - 1][x - 1] * angle->z / 10;
	start->x -= map[y - 1][x - 1] * angle->z / 10;
}

//remove start and stop by returning double
void	remove_height(int **map, xyz *start, xyz *stop, xyz *angle, int call, int x, int y)
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
	stop->y += map[y - a][x - b] * angle->z / 10;
	stop->x += map[y - a][x - b] * angle->z / 10;
	start->y += map[y - 1][x - 1] * angle->z / 10;
	start->x += map[y - 1][x - 1] * angle->z / 10;
}

void	ft_printer(void **mlx, xyz *angle, xyz start, xyz stop)
{
	static int	**map = NULL;
	static int	width;
	static int	height;
	int			x;
	int			y;

	if (!map)
		map = make_map((char *)mlx[2], &width, &height);
	y = height + 1;
	while (--y > 0 && (x = width))
		while (x > 0)
		{
			start.x += angle->z;
			stop.x += angle->z;
			if (x > 1)
			{
				add_height(map, &start, &stop, angle, 1, x, y);
				print_line(&start, &stop, mlx, 0xFF0000);
				remove_height(map, &start, &stop, angle, 1, x, y);
			}
			stop.x -= angle->z;
			stop.y += angle->z;
			if (y > 1)
			{
				add_height(map, &start, &stop, angle, 0, x, y);
				print_line(&start, &stop, mlx, 0xFF0000);
				remove_height(map, &start, &stop, angle, 0, x, y);
			}
			printer2(&start, &stop, angle);
			if (!--x)
				printer3(&start, &stop, angle, width);
		}
}
