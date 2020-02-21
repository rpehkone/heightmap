/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:19:28 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/21 16:46:07 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_abs(double n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

void	print_line(t_xyz start, t_xyz stop, void **mlx)
{
	t_xyz	step;
	t_xyz	pos;
	int		i;

	i = 0;
	start.x += 500;
	start.y += 500;
	stop.x += 500;
	stop.y += 500;
	pos.x = start.x;
	pos.y = start.y;
	pos.z = 0;
	step.z = ft_abs(stop.x - start.x) > ft_abs(stop.y - start.y) ?
			ft_abs(stop.x - start.x) : ft_abs(stop.y - start.y);
	step.x = (stop.x - start.x) / (float)step.z;
	step.y = (stop.y - start.y) / (float)step.z;
	while (pos.z <= step.z && i < 1000)
	{
		image_pixel_put(mlx, pos.x, pos.y - 200, 0x00FF00);
		pos.x += step.x;
		pos.y += step.y;
		pos.z++;
		i++;
	}
}

/*
void	print_line(t_xyz *start, t_xyz *stop, void **mlx)
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
	unsigned int fade;
	unsigned int color1 = 0xFF0000;
	unsigned int color2 = 0xFF00;
	while (pos.z <= step.z)
	{
		//image_pixel_put(mlx, pos.x, pos.y, *(int*)mlx[3]);
		fade = 0xFF * ((pos.z) / step.z);
		fade = fade << 4 * 6;
		if (fade < 0)
			fade = 0xFF000000;
		image_pixel_put(mlx, pos.x, pos.y, color2 + (0xFF000000 - fade));
		image_pixel_put(mlx, pos.x, pos.y, color1 + fade);

		//0xFF0000 * ((pos.z) / step.z);
		//ft_abs(color1 - color2) / step.x * pos.z;
		pos.x += step.x;
		pos.y += step.y;
		pos.z++;
	}
}
*/
