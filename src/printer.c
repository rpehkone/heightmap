/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:44:10 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/06 21:01:54 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	{
		color.x = set;
		color.y = set;
	}
	if (get_settings(7, NULL))
		return (add_color_height(color));
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
		save_coord(i, i + 1, 0);
		if ((i + 1) % width)
		{
			start = nodes[i];
			stop = nodes[i + 1];
			center_image(&start, &stop, mlx);
		}
		save_coord(i, i + width, 0);
		if (i + width < map_len)
		{
			start = nodes[i];
			stop = nodes[i + width];
			center_image(&start, &stop, mlx);
		}
	}
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
		slider(mlx, &i, 0);
	else if (get_settings(5, NULL))
		gradient(mlx);
	if (get_settings(6, NULL))
		get_color(-2);
}
