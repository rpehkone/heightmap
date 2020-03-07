/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:28:22 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 18:27:03 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_slider_button(void **mlx, int x)
{
	t_xyz	start;
	t_xyz	stop;
	t_xyz	color;
	int		i;

	color.x = 0xFFFFFF;
	color.y = 0xFFFFFF;
	color.z = 1;
	start.x = x;
	start.y = 38;
	stop.x = x;
	stop.y = 49;
	print_line(start, stop, color, mlx);
	i = 0;
	while (i < 5)
	{
		start.x++;
		stop.x++;
		print_line(start, stop, color, mlx);
		i++;
	}
}

void	slider_button(void **mlx, int *n, int reset)
{
	static int	slider_x = 205;
	static int	allow_move = 0;
	t_xyz		cursor;

	if (reset)
	{
		slider_x = 205;
		return ;
	}
	cursor = get_cursor(0, 0, NULL);
	if (cursor.x < 5)
		cursor.x = 5;
	if (cursor.x > 205)
		cursor.x = 205;
	if (cursor.x < 110 && cursor.x > 100)
		cursor.x = 105;
	if (cursor.x < slider_x + 10 && cursor.x > slider_x - 5 &&
		cursor.y > 30 && cursor.y < 55)
		allow_move = 1;
	if (!is_mouse_down(0, 1))
		allow_move = 0;
	if (allow_move)
		slider_x = cursor.x;
	(*n) = slider_x * 5;
	print_slider_button(mlx, slider_x);
}

void	print_mid(void **mlx)
{
	t_xyz	start;
	t_xyz	stop;
	t_xyz	color;
	int		i;

	color.x = 0x707070;
	color.y = 0x707070;
	color.z = 1;
	start.x = 106;
	start.y = 40;
	stop.x = 106;
	stop.y = 47;
	i = 0;
	while (i < 3)
	{
		start.x++;
		stop.x++;
		print_line(start, stop, color, mlx);
		i++;
	}
}

void	check_collision(void)
{
	t_xyz	cursor;

	if (is_mouse_down(0, 1))
	{
		cursor = get_cursor(0, 0, NULL);
		if (cursor.x < 311 && (cursor.y < 200 && cursor.y > 30))
			return ;
		else if (cursor.y > 30)
			get_settings(-2, NULL);
	}
}

void	slider(void **mlx, int *n)
{
	t_xyz	start;
	t_xyz	stop;
	t_xyz	color;
	int		i;

	print_mid(mlx);
	color.x = 0x707070;
	color.y = 0x707070;
	color.z = 1;
	start.x = 5;
	start.y = 41;
	stop.x = 210;
	stop.y = 41;
	i = 0;
	while (i < 4)
	{
		start.y++;
		stop.y++;
		print_line(start, stop, color, mlx);
		i++;
	}
	check_collision();
	slider_button(mlx, n, 0);
}
