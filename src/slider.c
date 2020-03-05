/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:28:22 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/05 17:23:04 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	slider_button(void **mlx, int *n, int move)
{
	t_xyz	start;
	t_xyz	stop;
	t_xyz	color;
	t_xyz	cursor;
	int		i;

	color.x = 0xFFFFFF;
	color.y = 0xFFFFFF;
	color.z = 1;
	cursor = get_cursor(0, 0, NULL);
	start.x = cursor.x;
	start.y = 38;
	stop.x = cursor.x;
	stop.y = 49;
	if (start.x < 5)
		start.x = 5;
	if (start.x > 150)
		start.x = 150;
	if (stop.x < 5)
		stop.x = 5;
	if (stop.x > 150)
		stop.x = 150;
	print_line(start, stop, color, mlx);
	i = 0;
	while (i < 5)
	{
		start.x++;
		stop.x++;
		print_line(start, stop, color, mlx);
		i++;
	}
	(void)n;
	(void)move;
}

void	slider(void **mlx, int *n, int move)
{
	t_xyz start;
	t_xyz stop;
	t_xyz color;

	color.x = 0x707070;
	color.y = 0x707070;
	color.z = 1;
	start.x = 5;
	start.y = 42;
	stop.x = 155;
	stop.y = 42;
	print_line(start, stop, color, mlx);
	start.y++;
	stop.y++;
	print_line(start, stop, color, mlx);
	start.y++;
	stop.y++;
	print_line(start, stop, color, mlx);
	start.y++;
	stop.y++;
	print_line(start, stop, color, mlx);
	slider_button(mlx, n, move);
}
