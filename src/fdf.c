/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/05 12:11:32 by rpehkone         ###   ########.fr       */
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

void	center_image(t_xyz *start, t_xyz *stop)
{
	static int x = 0;
	static int y = 0;

	if (!x)
	{
		x = get_width(NULL) / 2;
		y = get_height(NULL) / 2;
	}
	start->x += x;
	start->y += y;
	stop->x += x;
	stop->y += y;
}

void	add_perspective(t_xyz *start, t_xyz *stop, void **mlx)
{
	static int		focal_len = 1000;

	start->x /= ((start->z) / focal_len);
	start->y /= ((start->z) / focal_len);
	stop->x /= ((stop->z) / focal_len);
	stop->y /= ((stop->z) / focal_len);
	if (get_settings(4, NULL))
		slider(mlx, &focal_len, 0);
}

void	draw2(t_xyz *nodes, int map_len, void **mlx)
{
	t_xyz			start;
	t_xyz			stop;
	static int		width = 0;
	static t_xyz	color;
	int				i;

	if (!width)
	{
		width = get_map_width(0);
		color.x = 0xFFFFFF;
		color.y = 0xFF0000;
	}
	i = -1;
	while (++i < map_len)
	{
		if ((i + 1) % width)
		{
			start = nodes[i];
			stop = nodes[i + 1];
			if (!get_settings(1, NULL))
				add_perspective(&start, &stop, mlx);
			center_image(&start, &stop);
			print_line(start, stop, color, mlx);
		}
		if (i + width < map_len)
		{
			start = nodes[i];
			stop = nodes[i + width];
			if (!get_settings(1, NULL))
				add_perspective(&start, &stop, mlx);
			center_image(&start, &stop);
			print_line(start, stop, color, mlx);
		}
	}
	if (get_settings(5, NULL))
		gradient(mlx);
	else if (get_settings(6, NULL))
		cycle_colors(&color);
}

void	draw(t_xyz *nodes, int map_len, void **mlx)
{
	int		origo_len;
	int		i;

	origo_len = 900;
	i = -1;
	while (i++ < map_len)
		nodes[i].z += origo_len;
	draw2(nodes, map_len, mlx);
	i = -1;
	while (i++ < map_len)
		nodes[i].z -= origo_len;
	if (get_settings(2, NULL))
		slider(mlx, &origo_len, 0);
}

void	matrix_transform(t_xyz *nodes, int amount)
{
	static int	x = 0;
	static int	y = 0;
	t_xyz		cursor;
	int			i;

	cursor = get_cursor(0, 0, NULL);
	if (get_settings(0, NULL) && is_mouse_down(0, 1))
		rotate_y(-1 * (float)0.01 * (x - cursor.x), nodes, amount);
	if (get_settings(0, NULL) && is_mouse_down(0, 1))
		rotate_x((float)0.01 * (y - cursor.y), nodes, amount);
	if (get_settings(0, NULL) && is_mouse_down(0, 3) && !(i = 0))
		while (i < amount)
		{
			nodes[i].x -= x - cursor.x;
			nodes[i].y -= y - cursor.y;
			i++;
		}
	if (get_settings(0, NULL) && is_mouse_down(0, 4) && (i = -1))
		while (i++ < amount)
			nodes[i].z += 50;
	if (get_settings(0, NULL) && is_mouse_down(0, 5) && (i = -1))
		while (i++ < amount)
			nodes[i].z -= 50;
	x = cursor.x;
	y = cursor.y;
}

int		matrix(void **mlx)
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
	matrix_transform(nodes, amount);
	draw(nodes, amount, mlx);
	return (0);
}

#include <sys/time.h>

void	fps(void **mlx)
{
	struct timeval	time;
	static long		s = 0;
	static int		i = 0;
	static int		fps = 0;
	static int		height = 0;

	i++;
	if (!height)
		height = get_height(NULL);
	gettimeofday(&time, NULL);
	mlx_string_put(mlx[0], mlx[1], 10, height - 30, 0xFFFF00, ft_itoa(fps));
	if (s != time.tv_sec)
	{
		s = time.tv_sec;
		fps = i;
		i = 0;
	}
}

int		fdf(void **mlx)
{
	matrix(mlx);
	buttons_loop(mlx);
	help_text(mlx);
	fps(mlx);
	return (0);
}
