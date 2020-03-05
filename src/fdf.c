/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/05 14:31:55 by rpehkone         ###   ########.fr       */
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

void	add_perspective(t_xyz *start, t_xyz *stop)
{
	static int		focal_len = 1000;

	start->x /= ((start->z) / focal_len);
	start->y /= ((start->z) / focal_len);
	stop->x /= ((stop->z) / focal_len);
	stop->y /= ((stop->z) / focal_len);
}

t_xyz	get_color(int set)
{
	static t_xyz	color = {.x = -1};

	if (color.x == -1)
	{
		color.x = 0xFFFFFF;
		color.y = 0xFFFFFF;
		color.z = 0;
	}
	if (set == -2)
		cycle_colors(&color);
	else if (set)
		color.x = set;
	return (color);
}

void	move_center(t_xyz *start, t_xyz *stop, void **mlx)
{
	static double	zoom = -500;

	if (get_settings(0, NULL) && is_mouse_down(0, 4))
		zoom += 0.1;
	if (get_settings(0, NULL) && is_mouse_down(0, 5))
		zoom -= 0.1;
	start->z -= zoom;
	stop->z -= zoom;
	if (!get_settings(1, NULL))
		add_perspective(start, stop);
	print_line(*start, *stop, get_color(0), mlx);
}

void	center_image(t_xyz *start, t_xyz *stop, void **mlx)
{
	static int	x = 0;
	static int	y = 0;
	static int	coordx = 0;
	static int	coordy = 0;
	t_xyz		cursor;

	cursor = get_cursor(0, 0, NULL);
	if (!x)
	{
		x = get_width(NULL) / 2;
		y = get_height(NULL) / 2;
		x = 0;
		y = -200;
	}
	if (get_settings(0, NULL) && is_mouse_down(0, 3))
		x -= coordx - cursor.x;
	if (get_settings(0, NULL) && is_mouse_down(0, 3))
		y -= coordy - cursor.y;
	coordx = cursor.x;
	coordy = cursor.y;
	start->x += x;
	start->y += y;
	stop->x += x;
	stop->y += y;
	move_center(start, stop, mlx);
}

void	draw2(t_xyz *nodes, int map_len, void **mlx)
{
	t_xyz			start;
	t_xyz			stop;
	static int		width = 0;
	int				i;

	if (!width)
		width = get_map_width(0);
	i = -1;
	while (++i < map_len)
	{
		if ((i + 1) % width)
		{
			start = nodes[i];
			stop = nodes[i + 1];
			center_image(&start, &stop, mlx);
		}
		if (i + width < map_len)
		{
			start = nodes[i];
			stop = nodes[i + width];
			center_image(&start, &stop, mlx);
		}
	}
	if (get_settings(6, NULL))
		get_color(-2);
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
	else if (get_settings(4, NULL))
		slider(mlx, &i, 0);//add_perspective(NULL, focal_len)
	else if (get_settings(5, NULL))
		gradient(mlx);
}

void	matrix_transform(t_xyz *nodes, int amount)
{
	static int	x = 0;
	static int	y = 0;
	t_xyz		cursor;

	cursor = get_cursor(0, 0, NULL);
	if (get_settings(3, NULL))
		rotate_y((float)0.01, nodes, amount);
	if (get_settings(0, NULL) && is_mouse_down(0, 1))
		rotate_y(-1 * (float)0.01 * (x - cursor.x), nodes, amount);
	if (get_settings(0, NULL) && is_mouse_down(0, 1))
		rotate_x((float)0.01 * (y - cursor.y), nodes, amount);
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
	if (get_settings(8, NULL))
		mlx_string_put(mlx[0], mlx[1], 10,
		height - 30, 0xFFFF00, ft_itoa(fps));
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
