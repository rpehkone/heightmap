/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:50:23 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 21:38:10 by rpehkone         ###   ########.fr       */
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

void	add_perspective(t_xyz *start, t_xyz *stop, int reset)
{
	static float		focal_len = 1;

	if (reset)
	{
		focal_len = 1;
		return ;
	}
	if (get_settings(2, NULL))
		slider(&focal_len);
	int focal_len2 = (focal_len + 2) * 500;
	start->x /= ((start->z) / (focal_len2));
	start->y /= ((start->z) / (focal_len2));
	stop->x /= ((stop->z) / (focal_len2));
	stop->y /= ((stop->z) / (focal_len2));
}
