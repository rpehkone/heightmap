/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/04 21:16:57 by rpehkone         ###   ########.fr       */
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
	static int focal_len = 1000;

	if (!settings)
		settings = get_settings();
	settings[1] = 1;
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
	if (settings[2])
		slider(mlx, NULL, 0);
	else if (settings[4])
		slider(mlx, &focal_len, 0);
}

void	matrix_transform(t_xyz *nodes, int amount, int allow_to_move)
{
	static int	x = 0;
	static int	y = 0;
	t_xyz		cursor;
	int			i;

	cursor = get_cursor(0, 0, NULL);
	if (allow_to_move && is_mouse_down(0, 1))
		rotate_y(-1 * (float)0.01 * (x - cursor.x), nodes, amount);
	if (allow_to_move && is_mouse_down(0, 1))
		rotate_x((float)0.01 * (y - cursor.y), nodes, amount);
	if (allow_to_move && is_mouse_down(0, 3) && !(i = 0))
		while (i < amount)
		{
			nodes[i].x -= x - cursor.x;
			nodes[i].y -= y - cursor.y;
			i++;
		}
	if (allow_to_move && is_mouse_down(0, 4) && (i = -1))
		while (i++ < amount)
			nodes[i].z += 50;
	if (allow_to_move && is_mouse_down(0, 5) && (i = -1))
		while (i++ < amount)
			nodes[i].z -= 50;
	x = cursor.x;
	y = cursor.y;
}

int		matrix(void **mlx, int allow_to_move)
{
	static t_xyz	*nodes = NULL;
	static int		amount = 0;

	if (!nodes)
		nodes = make_map(NULL);
	if (!amount)
		amount = get_map_len(0);
	mlx_clear_window(mlx[0], mlx[1]);
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
	mlx_clear_image(mlx);
	matrix_transform(nodes, amount, allow_to_move);
	draw(nodes, mlx);
	return (0);
}

int		fdf(void **mlx)
{
	static int	allow_rotate = 1;

	matrix(mlx, allow_rotate);
	allow_rotate = buttons_loop(mlx);
	help_text(mlx);
	return (0);
}
