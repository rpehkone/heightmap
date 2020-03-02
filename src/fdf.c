/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/02 18:18:28 by rpehkone         ###   ########.fr       */
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

/*tee dolly zoom*/

void	draw(t_xyz *nodes, void **mlx, int perspective)
{
	t_xyz		start;
	t_xyz		stop;
	static int	map_len = 0;
	static int	width = 0;

	int focal_len = 1000;
	int origo_len = 1000;
	if (!map_len)
		map_len = get_map_len(0);
	if(!width)
		width = get_map_width(0);
	for (int i = 0; i < map_len; i++)
	{
		nodes[i].z += origo_len;
	}
	for (int i = 0; i < map_len - 1; i++)
	{
		if ((i + 1) % width)
		{
			start = nodes[i];
			stop = nodes[i + 1];
			if (perspective)
			{
				start.x /= ((start.z) / focal_len);
				start.y /= ((start.z) / focal_len);
				stop.x /= ((stop.z) / focal_len);
				stop.y /= ((stop.z) / focal_len);
			}
			print_line(start, stop, mlx);
		}
		if (i + width < map_len)
		{
			start = nodes[i];
			stop = nodes[i + width];
			if (perspective)
			{
				start.x /= ((start.z) / focal_len);
				start.y /= ((start.z) / focal_len);
				stop.x /= ((stop.z) / focal_len);
				stop.y /= ((stop.z) / focal_len);
			}
			print_line(start, stop, mlx);
		}
	}
	for (int i = 0; i < map_len; i++)
	{
		nodes[i].z -= origo_len;
	}
}

int		mouse_movement(int call, int x, int y, t_xyz *nodes)
{
	static int	m1_down = 0;
	static int	oldy = 0;
	static int	oldx = 0;
	static int	asd = 0;
	static int	amount = 0;

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
		if (!amount)
			amount = get_map_len(0);
		rotateY(-1 * (float)0.01 * (oldx - x), nodes, amount);
		rotateX((float)0.01 * (oldy - y), nodes, amount);
		oldx = x;
		oldy = y;
	}
	//auto rotate;
//	rotateY(0.01, nodes, amount);
	return (asd);
}

int		matrix(int call, int x, int y, void **mlx)
{
	static t_xyz	*nodes = NULL;

	if (!nodes)
		nodes = make_map(NULL);
	if (call != 10)
		mouse_movement(call, x, y, nodes);
	mlx_clear_window(mlx[0], mlx[1]);
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
	mlx_clear_image(mlx);
	draw(nodes, mlx, 0);
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
	//wront w * h
	//help_text(mlx);
	return (0);
}
