/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:28:22 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/03 19:43:14 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	slider(void **mlx)
{
	//int arg and return edited?
	t_xyz start;
	t_xyz stop;
	t_xyz color;

	color.x = 0xFFFFFF;
	color.y = 0xFFFFFF;
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
}
