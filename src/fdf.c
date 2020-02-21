/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/21 17:04:40 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotateX(float theta, t_xyz *nodes, int amount)
{
    double	sinTheta;
    double	cosTheta;
	float	y;
	float	z;
	int		n;

	n = 0;
    sinTheta = sin(theta);
    cosTheta = cos(theta);
	while (n < amount)
	{
        y = nodes[n].y;
        z = nodes[n].z;
        nodes[n].y = y * cosTheta - z * sinTheta;
        nodes[n].z = z * cosTheta + y * sinTheta;
		n++;
    }
}

void	rotateY(float theta, t_xyz *nodes, int amount)
{
    double	sinTheta;
    double	cosTheta;
	float	x;
	float	z;
	int		n;

	n = 0;
    sinTheta = sin(theta);
    cosTheta = cos(theta);
	while (n < amount)
	{
		x = nodes[n].x;
		z = nodes[n].z;
		nodes[n].x = x * cosTheta + z * sinTheta;
		nodes[n].z = z * cosTheta - x * sinTheta;
		n++;
	}
}

void	rotateZ(float theta, t_xyz *nodes, int amount)
{
	double	sinTheta;
	double	cosTheta;
	float	x;
	float	y;
	int		n;

	n = 0;
    sinTheta = sin(theta);
    cosTheta = cos(theta);
	while (n < amount)
	{
		x = nodes[n].x;
		y = nodes[n].y;
		nodes[n].x = x * cosTheta - y * sinTheta;
		nodes[n].y = y * cosTheta + x * sinTheta;
		n++;
	}
}

void	dot(int x, int y, int z, void **mlx)
{
	x += 500;
	y += 300;
	mlx_pixel_put(mlx[0], mlx[1], x, y, 0xFF0000);
	mlx_pixel_put(mlx[0], mlx[1], x + 1, y, 0xFF0000);
	mlx_pixel_put(mlx[0], mlx[1], x, y + 1, 0xFF0000);
	mlx_pixel_put(mlx[0], mlx[1], x + 1, y + 1, 0xFF0000);
	(void)z;
}

// tee dolly zoom

void	draw(t_xyz *nodes, t_xyz *lines, void **mlx)
{
	t_xyz	start;
	t_xyz	stop;

	for (int i = 0; i <= 7; i++)
	{
		//nodes[i].x += 500;
		//nodes[i].y += 500;
		nodes[i].z += 700;
	}
	for (int i = 0; i < 12; i++)
	{
		start = nodes[(int)lines[i].x];
		stop = nodes[(int)lines[i].y];
		//perspective
		start.x /= ((start.z) / 1000);
		start.y /= ((start.z) / 1000);
		stop.x /= ((stop.z) / 1000);
		stop.y /= ((stop.z) / 1000);

		print_line(start, stop, mlx);
	}
	for (int i = 0; i <= 7; i++)
	{
		dot(nodes[i].x, nodes[i].y, nodes[i].z, mlx);
		//nodes[i].x -= 500;
		//nodes[i].y -= 500;
		nodes[i].z -= 700;
	}
}

int		mouse_movement(int call, int x, int y, t_xyz *nodes)
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
		rotateY(-1 * (float)0.01 * (oldx - x), nodes, 8);
		rotateX((float)0.01 * (oldy - y), nodes, 8);
		//auto rotate rotateX(0.005, nodes);
		oldx = x;
		oldy = y;
	}
	return (asd);
}

int		matrix(int call, int x, int y, void **mlx)
{
	static t_xyz	*nodes = NULL;
	static t_xyz	*lines = NULL;

	if (!lines)
	{
		lines = (t_xyz*)malloc(sizeof(t_xyz) * 12);
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
		nodes = (t_xyz*)malloc(sizeof(t_xyz) * 8);
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
	}
	if (call != 10)
		mouse_movement(call, x, y, nodes);
	mlx_clear_window(mlx[0], mlx[1]);
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
	mlx_clear_image(mlx);
	draw(nodes, lines, mlx);
	return (0);
}

int		fdf(int call, int x, int y, void **mlx)
{
	static int	allow_rotate = 1;

	if (allow_rotate)
		matrix(call, x, y, mlx);
	else
		matrix(10, x, y, mlx);
	//allow_rotate = buttons_main(call, x, y, mlx);
	help_text(mlx);
	return (0);
}
