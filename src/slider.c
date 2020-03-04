/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:28:22 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/03 20:11:06 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	slider(void **mlx, int *n, int move)
{
	//int arg and return edited?
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

	(void)n;
	(void)move;
	color.x = 0xFFFFFF;
	color.y = 0xFFFFFF;
	start.x = 5;//*n;
	start.y = 38;
	stop.x = 5;//*n;
	stop.y = 49;
	print_line(start, stop, color, mlx);
	start.x++;
	stop.x++;
	print_line(start, stop, color, mlx);
	start.x++;
	stop.x++;
	print_line(start, stop, color, mlx);
	start.x++;
	stop.x++;
	print_line(start, stop, color, mlx);
	start.x++;
	stop.x++;
	print_line(start, stop, color, mlx);
	start.x++;
	stop.x++;
	print_line(start, stop, color, mlx);
	//(*n) += 10;
}
