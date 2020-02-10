/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/10 17:51:22 by rpehkone         ###   ########.fr       */
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

void	add_height_horiz(t_xyz *start, t_xyz *stop, t_xyz *coord, void **mlx)
{
	static int	**map = NULL;

	if (!map)
		map = make_map((char *)mlx[2]);
	stop->y -= map[(int)coord->y + 0]
		[(int)coord->x + (0 * -1) + 1] * (int)coord->z / 10;
	stop->x -= map[(int)coord->y + 0]
		[(int)coord->x + (0 * -1) + 1] * (int)coord->z / 10;
	start->y -= map[(int)coord->y]
		[(int)coord->x] * (int)coord->z / 10;
	start->x -= map[(int)coord->y]
		[(int)coord->x] * (int)coord->z / 10;
	print_line(start, stop, mlx, 0xFF0000);
	stop->y += map[(int)coord->y + 0]
		[(int)coord->x + (0 * -1) + 1] * (int)coord->z / 10;
	stop->x += map[(int)coord->y + 0]
		[(int)coord->x + (0 * -1) + 1] * (int)coord->z / 10;
	start->y += map[(int)coord->y]
		[(int)coord->x] * (int)coord->z / 10;
	start->x += map[(int)coord->y]
		[(int)coord->x] * (int)coord->z / 10;
}

void	add_height_verti(t_xyz *start, t_xyz *stop, t_xyz *coord, void **mlx)
{
	static int	**map = NULL;

	if (!map)
		map = make_map((char *)mlx[2]);
	stop->y -= map[(int)coord->y + 1]
		[(int)coord->x + (1 * -1) + 1] * (int)coord->z / 10;
	stop->x -= map[(int)coord->y + 1]
		[(int)coord->x + (1 * -1) + 1] * (int)coord->z / 10;
	start->y -= map[(int)coord->y]
		[(int)coord->x] * (int)coord->z / 10;
	start->x -= map[(int)coord->y]
		[(int)coord->x] * (int)coord->z / 10;
	print_line(start, stop, mlx, 0xFF0000);
	stop->y += map[(int)coord->y + 1]
		[(int)coord->x + (1 * -1) + 1] * (int)coord->z / 10;
	stop->x += map[(int)coord->y + 1]
		[(int)coord->x + (1 * -1) + 1] * (int)coord->z / 10;
	start->y += map[(int)coord->y]
		[(int)coord->x] * (int)coord->z / 10;
	start->x += map[(int)coord->y]
		[(int)coord->x] * (int)coord->z / 10;
}

void	ft_printer(void **mlx, t_xyz *angle, t_xyz start, t_xyz stop)
{
	static int	width = 0;
	static int	height = 0;
	int			x;
	int			y;

	if (!width)
		width = get_width(mlx[2]);
	if ((y = -1) && !height)
		height = get_height(mlx[2]);
	while (++y < height && (x = -1))
	{
		while (++x < width)
		{
			start.x += angle->z;
			stop.x += angle->z;
			if (x < width - 1)
				add_height_horiz(&start, &stop, get_coord(x, y, *angle), mlx);
			stop.x -= angle->z;
			stop.y += angle->z;
			if (y < height - 1)
				add_height_verti(&start, &stop, get_coord(x, y, *angle), mlx);
			next_spot(&start, &stop, angle);
		}
		row_start(&start, &stop, angle, width);
	}
}
