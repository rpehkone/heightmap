/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:28:22 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/04 23:48:36 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	slider_button(void **mlx, int *n, int move)
{
	t_xyz	start;
	t_xyz	stop;
	t_xyz	color;
	int		i;

	color.x = 0xFFFFFF;
	color.y = 0xFFFFFF;
	start.x = 5;
	start.y = 38;
	stop.x = 5;
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
