/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 13:59:34 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		print_button2(t_xyz *start, t_xyz *stop, int color, void **mlx)
{
	t_xyz	step;
	t_xyz	pos;

	pos.x = start->x;
	pos.y = start->y;
	pos.z = 0;
	step.z = ft_abs(stop->x - start->x) > ft_abs(stop->y - start->y) ?
			ft_abs(stop->x - start->x) : ft_abs(stop->y - start->y);
	step.x = (stop->x - start->x) / (float)step.z;
	step.y = (stop->y - start->y) / (float)step.z;
	while (pos.z <= step.z)
	{
		image_pixel_put(mlx, pos.x, pos.y, color);
		pos.x += step.x;
		pos.y += step.y;
		pos.z++;
	}
}

void		print_edge(t_xyz start, t_xyz stop, t_button *b, void **mlx)
{
	start.x = b->x;
	start.y = b->y;
	stop.x = b->x + b->size_x;
	stop.y = b->y;
	print_button2(&start, &stop, b->edge_color, mlx);
	stop.x = b->x;
	stop.y = b->y + b->size_y;
	print_button2(&start, &stop, b->edge_color, mlx);
	start.x = b->x;
	start.y = b->y + b->size_y;
	stop.x = b->x + b->size_x;
	stop.y = b->y + b->size_y;
	print_button2(&start, &stop, b->edge_color, mlx);
	start.x = b->x + b->size_x;
	start.y = b->y;
	stop.x = b->x + b->size_x;
	stop.y = b->y + b->size_y;
	print_button2(&start, &stop, b->edge_color, mlx);
}

void		print_button(t_button *b, void **mlx)
{
	t_xyz start;
	t_xyz stop;

	start.x = b->x;
	start.y = b->y;
	stop.x = b->x + b->size_x;
	stop.y = b->y;
	while (start.y < b->y + b->size_y)
	{
		print_button2(&start, &stop, b->b_color, mlx);
		start.y++;
		stop.y++;
	}
	mlx_string_put(mlx[0], mlx[1], b->x + 6,
			b->y + 3, b->t_color, b->text);
	if (b->edge)
		print_edge(start, stop, b, mlx);
}
