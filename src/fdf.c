/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/03 19:43:52 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_x(float angle, t_xyz *nodes, int amount)
{
	double	sin_angle;
	double	cos_angle;
	float	y;
	float	z;
	int		n;

	n = 0;
	sin_angle = sin(angle);
	cos_angle = cos(angle);
	while (n < amount)
	{
		y = nodes[n].y;
		z = nodes[n].z;
		nodes[n].y = y * cos_angle - z * sin_angle;
		nodes[n].z = z * cos_angle + y * sin_angle;
		n++;
	}
}

void	rotate_y(float angle, t_xyz *nodes, int amount)
{
	double	sin_angle;
	double	cos_angle;
	float	x;
	float	z;
	int		n;

	n = 0;
	sin_angle = sin(angle);
	cos_angle = cos(angle);
	while (n < amount)
	{
		x = nodes[n].x;
		z = nodes[n].z;
		nodes[n].x = x * cos_angle + z * sin_angle;
		nodes[n].z = z * cos_angle - x * sin_angle;
		n++;
	}
}

void	rotate_z(float angle, t_xyz *nodes, int amount)
{
	double	sin_angle;
	double	cos_angle;
	float	x;
	float	y;
	int		n;

	n = 0;
	sin_angle = sin(angle);
	cos_angle = cos(angle);
	while (n < amount)
	{
		x = nodes[n].x;
		y = nodes[n].y;
		nodes[n].x = x * cos_angle - y * sin_angle;
		nodes[n].y = y * cos_angle + x * sin_angle;
		n++;
	}
}

void	draw(t_xyz *nodes, void **mlx)
{
	t_xyz		start;
	t_xyz		stop;
	static int	map_len = 0;
	static int	width = 0;
	static int	*settings = NULL;
	static t_xyz	color = {.x = 0xFFFFFF, .y = 0xFF0000};

	if (!settings)
		settings = get_settings();
	int focal_len = 1000;
	int origo_len = 900;
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
			if (settings[1])
			{
				start.x /= ((start.z) / focal_len);
				start.y /= ((start.z) / focal_len);
				stop.x /= ((stop.z) / focal_len);
				stop.y /= ((stop.z) / focal_len);
			}
			print_line(start, stop, color, mlx);
		}
		if (i + width < map_len)
		{
			start = nodes[i];
			stop = nodes[i + width];
			if (settings[1])
			{
				start.x /= ((start.z) / focal_len);
				start.y /= ((start.z) / focal_len);
				stop.x /= ((stop.z) / focal_len);
				stop.y /= ((stop.z) / focal_len);
			}
			print_line(start, stop, color, mlx);
		}
	}
	for (int i = 0; i < map_len; i++)
	{
		nodes[i].z -= origo_len;
	}
	if (settings[5])
		gradient(mlx);
	if (settings[6])
		cycle_colors(&color);
	if (settings[2] || settings[4])
		slider(mlx);
}

int		mouse_movement(int call, int x, int y, t_xyz *nodes)
{
	static int	m1_down = 0;
	static int	m3_down = 0;
	static int	oldy = 0;
	static int	oldx = 0;
	static int	asd = 0;
	static int	amount = 0;

	if (!amount)
		amount = get_map_len(0);
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
	if (call == 10 || (call == 5 && x == 1))
		m1_down = 0;
	if (call == 4 && x == 3)
		m3_down = 1;
	if (call == 10 || (call == 5 && x == 3))
		m3_down = 0;
	if (call == 4 && x == 5)
		for (int i = 0; i < amount; i++)
			nodes[i].z += 50;
	if (call == 4 && x == 4)
		for (int i = 0; i < amount; i++)
			nodes[i].z -= 50;
	if (call == 6 && m3_down)
	{
		for (int i = 0; i < amount; i++)
		{
			nodes[i].x -= oldx - x;
			nodes[i].y -= oldy - y;
		}
		oldx = x;
		oldy = y;
	}
	if (call == 6 && m1_down)
	{
		rotate_y(-1 * (float)0.01 * (oldx - x), nodes, amount);
		rotate_x((float)0.01 * (oldy - y), nodes, amount);
		oldx = x;
		oldy = y;
	}
	static int *settings = NULL;
	if (!settings)
		settings = get_settings();
	if (settings[3])
	{
		rotate_x(0.01, nodes, amount);
		rotate_y(0.01, nodes, amount);
		rotate_z(0.01, nodes, amount);
	}
	return (asd);
}

int		matrix(int call, int x, int y, void **mlx)
{
	static t_xyz	*nodes = NULL;

	if (!nodes)
		nodes = make_map(NULL);
	mouse_movement(call, x, y, nodes);
	mlx_clear_window(mlx[0], mlx[1]);
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
	mlx_clear_image(mlx);
	draw(nodes, mlx);
	return (0);
}

int		fdf(int call, int x, int y, void **mlx)
{
	static int	allow_rotate = 1;

	if (allow_rotate)
		matrix(call, x, y, mlx);
	else
		matrix(10, x, y, mlx);
	allow_rotate = buttons_loop(call, x, y, mlx);
	help_text(mlx);
	return (0);
}
