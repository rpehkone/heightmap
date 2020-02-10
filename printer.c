/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/10 15:48:24 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	row_start(t_xyz *start, t_xyz *stop, t_xyz *angle, int width)
{
	start->x += angle->y;
	stop->x += angle->y;
	start->y += angle->z;
	stop->y += angle->z;
	start->y -= angle->x * (width - 1);
	stop->y -= angle->x * (width - 1);
	start->x -= angle->y * width;
	stop->x -= angle->y * width;
	while (width > 0)
	{
		start->x -= angle->z;
		stop->x -= angle->z;
		width--;
	}
}

void	next_spot(t_xyz *start, t_xyz *stop, t_xyz *angle)
{
	stop->x += angle->z;
	stop->y -= angle->z;
	start->y += angle->x;
	stop->y += angle->x;
	start->x += angle->y;
	stop->x += angle->y;
}

void	add_height(t_xyz *start, t_xyz *stop, t_xyz *angle, int call, int x, int y, void **mlx)
{
	static int	**map = NULL;

	if (!map)
		map = make_map((char *)mlx[2]);
	stop->y -= map[y - (2 - call)][x - (call + 1)] * angle->z / 10;
	stop->x -= map[y - (2 - call)][x - (call + 1)] * angle->z / 10;
	start->y -= map[y - 1][x - 1] * angle->z / 10;
	start->x -= map[y - 1][x - 1] * angle->z / 10;
	print_line(start, stop, mlx, 0xFF0000);
	stop->y += map[y - (2 - call)][x - (call + 1)] * angle->z / 10;
	stop->x += map[y - (2 - call)][x - (call + 1)] * angle->z / 10;
	start->y += map[y - 1][x - 1] * angle->z / 10;
	start->x += map[y - 1][x - 1] * angle->z / 10;
}

#include <stdio.h>
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
		printf("width = %d\n", width);
		printf("height = %d\n", height);
	}
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			start.x += angle->z;
			stop.x += angle->z;
			//	add_height(&start, &stop, angle, 1, x, y, mlx);
			if (x < width - 1)
				print_line(&start, &stop, mlx, 0xFF0000);
			stop.x -= angle->z;
			stop.y += angle->z;
			if (y < height - 1)
				print_line(&start, &stop, mlx, 0xFF0000);
			//	add_height(&start, &stop, angle, 0, x, y, mlx);
			next_spot(&start, &stop, angle);
			x++;
		}
		row_start(&start, &stop, angle, width);
		y++;
	}
}
