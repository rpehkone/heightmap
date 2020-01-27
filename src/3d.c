/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/16 20:15:20 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	dot(int x, int y, void **mlx)
{
		mlx_pixel_put(mlx[0], mlx[1], x, y, 0xFF0000);
		mlx_pixel_put(mlx[0], mlx[1], x + 1, y, 0xFF0000);
		mlx_pixel_put(mlx[0], mlx[1], x, y + 1, 0xFF0000);
		mlx_pixel_put(mlx[0], mlx[1], x + 1, y + 1, 0xFF0000);
}

void	draw(xyz *nodes, coords *lines, int color, void **mlx)
{
	for (int i = 0; i <= 7; i++)
	{
		nodes[i].x += 500;
		nodes[i].y += 500;
	}
	for (int i = 0; i < 12; i++)
	{
		print_line(&nodes[lines[i].x], &nodes[lines[i].y], mlx, color);
		dot(nodes[i].x, nodes[i].y, mlx);
	}
	for (int i = 0; i <= 7; i++)
	{
		nodes[i].x -= 500;
		nodes[i].y -= 500;
	}
}

int	mouse_movement(int call, int x, int y, xyz *nodes)
{
	static int	m1_down = 0;
	static int	oldy = 0;
	static int	oldx = 0;
	static int asd = 0;

	if (asd == 1)
	{
		oldx = x;
		oldy = y;
		asd = 0;
	}
	if (call == 4 && x == 1)
	{
		m1_down = 1;
		asd = 1;
	}
	if (call == 5 && x == 1)
		m1_down = 0;
	if (call == 6 && m1_down == 1)
	{
		//printf("oldx = %d\n", oldx);
		//printf("%d\n", oldx - x);
		rotateY(-1 * (float)0.01 * (oldx - x), nodes);
		rotateX((float)0.01 * (oldy - y), nodes);
		//auto rotate rotateX(0.005, nodes);
		oldx = x;
		oldy = y;
	}
	return (asd);
}

int		matrix(int call, int x, int y, void **mlx)
{
	static int	oldy = 0;
	static int	oldx = 0;
	static xyz	*nodes = NULL;
	static coords	*lines = NULL;
	static int	color = 0x00FF00;
	static button	b_color = {.x = 0, .y = 950, .size_x = 75, .size_y = 40, .b_color = 0x000000,
	.bc_color = 0xFFFFFF, .t_color = 0xFF0000, .tc_color = 0xFF0000, .type = 0, .text = "Color"};

	if (!lines)
	{
		lines = (coords*)malloc(sizeof(coords) * 12);
		lines[0].x = 0;
		lines[0].y = 1;

		lines[4].x = 0;
		lines[4].y = 2;

		lines[5].x = 0;
		lines[5].y = 4;

		lines[1].x = 1;
		lines[1].y = 3;

		lines[2].x = 1;
		lines[2].y = 5;

		lines[3].x = 2;
		lines[3].y = 3;

		lines[6].x = 2;
		lines[6].y = 6;

		lines[7].x = 3;
		lines[7].y = 7;

		lines[8].x = 4;
		lines[8].y = 5;

		lines[9].x = 4;
		lines[9].y = 6;

		lines[10].x = 5;
		lines[10].y = 7;

		lines[11].x = 6;
		lines[11].y = 7;

	}
	if (!nodes)
	{
		nodes = (xyz*)malloc(sizeof(xyz) * 8);
		nodes[0].x = -100;
		nodes[0].y = -100;
		nodes[0].z = -100;

		nodes[1].x = -100;
		nodes[1].y = -100;
		nodes[1].z = 100;

		nodes[2].x = -100;
		nodes[2].y = 100;
		nodes[2].z = -100;

		nodes[3].x = -100;
		nodes[3].y = 100;
		nodes[3].z = 100;

		nodes[4].x = 100;
		nodes[4].y = -100;
		nodes[4].z = -100;

		nodes[5].x = 100;
		nodes[5].y = -100;
		nodes[5].z = 100;

		nodes[6].x = 100;
		nodes[6].y = 100;
		nodes[6].z = -100;

		nodes[7].x = 100;
		nodes[7].y = 100;
		nodes[7].z = 100;

		//rotateZ((float)60, nodes);
		//rotateY((float)60, nodes);
		//rotateX((float)61, nodes);
	}
	if (call == 6)
	{
		oldx = x;
		oldy = y;
	}
	mouse_movement(call, x, y, nodes);
	mlx_clear_window(mlx[0], mlx[1]);
	draw(nodes, lines, color, mlx);
	static int grd = 0;
	if (grd)
	{
		gradient(.02,.02,.02,0,2,4, 128, 127, 310, mlx);
		if (call == 4 && x == 1)
		{
			int i = get_color(oldx, oldy - 600, .02,.02,.02,0,2,4, 128, 127, 310, mlx);
			if (i)
				color = i;
		}
	}
	if (handle_button(mlx, b_color, oldx, oldy))
	{
		if (call == 4 && x == 1)
			grd = grd ? 0 : 1;
	}
	return (0);
}
