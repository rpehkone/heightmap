/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/28 00:53:34 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	ft_printer(void **mlx, int **map, int x, int y, xyz *angle, int offset_x, int offset_y)
{
	xyz start = {.x = 0, .y = 0};
	xyz stop = {.x = angle->z + angle->y, .y = angle->x};
	int cpy;

	start.x += offset_x;
	start.y += offset_y;
	stop.x += offset_x;
	stop.y += offset_y;
	while (y > 0)
	{
		cpy = x;
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
		help_rotate(&start, &stop, angle, x);
		y--;
	}
}

void		mouse_control(int call, int x, int y, xyz *angle, int *offset_x, int *offset_y)
{
	//combine m1 and m3, and move start and stop here
	static int	m1_down = 0;
	static int	m3_down = 0;
	static int	old_x;
	static int	old_y;

	if (call == 6)
	{
		if (m1_down)
		{
			angle->y += x - old_x;
			angle->x += y - old_y;
		}
		else if (m3_down)
		{
			*offset_x += x - old_x;
			*offset_y += y - old_y;
		}

		old_x = x;
		old_y = y;
	}
	if (call == 4 && x == 1)
		m1_down = 1;
	if (call == 5 && x == 1)
		m1_down = 0;
	if (call == 4 && x == 4)
		angle->z += 1;
	if (call == 4 && x == 5)
		angle->z -= 1;
	if (call == 4 && x == 3)
		m3_down = 1;
	if (call == 5 && x == 3)
		m3_down = 0;
	if (angle->z < 0)
		angle->z = 0;
}

int		fdf(int call, int x, int y, void **mlx)
{
	static xyz	angle = {.x = 2, .y = -5, .z = 30};
	static int	**map = NULL;
	static int	width = 0;
	static int	height = 0;
	static int	offset_x = 200;
	static int	offset_y = 200;

	if (!map)
	{
		map = make_map((char *)mlx[2], &width, &height);
		angle.z = width + height;
		if (angle.z > 100)
			angle.z > 100;
	}
	mouse_control(call, x, y, &angle, &offset_x, &offset_y);
	mlx_clear_window(mlx[0], mlx[1]);
	ft_printer(mlx, map, width, height, &angle, offset_x, offset_y);
	return (0);
}
