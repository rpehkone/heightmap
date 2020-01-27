/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/12 18:51:13 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_line(xyz *start, xyz *stop, void **mlx, unsigned color)
{
	xyz	step;
	xyz	pos;

	pos.x = start->x;
	pos.y = start->y;
	pos.z = 0;
	step.z = ft_abs(stop->x - start->x) > ft_abs(stop->y - start->y) ?
			ft_abs(stop->x - start->x) : ft_abs(stop->y - start->y);
	step.x = (stop->x - start->x) / (float)step.z;
	step.y = (stop->y - start->y) / (float)step.z;
	while (pos.z <= step.z)
	{
		mlx_pixel_put(mlx[0], mlx[1], pos.x, pos.y, color);
		pos.x += step.x;
		pos.y += step.y;
		pos.z++;
	}
}

void	ft_point(void **mlx, particle p)
{
	mlx_pixel_put(mlx[0], mlx[1], p.x, p.y, p.color);
	mlx_pixel_put(mlx[0], mlx[1], p.x + 1, p.y, p.color);
	mlx_pixel_put(mlx[0], mlx[1], p.x - 1, p.y, p.color);
	mlx_pixel_put(mlx[0], mlx[1], p.x, p.y + 1, p.color);
	mlx_pixel_put(mlx[0], mlx[1], p.x, p.y - 1, p.color);
}

void	putcircle(coords *pos, int fill, int color, void **mlx)
{
	int		x;
	int		y;
	int		dst;

	y = 0;
	while (y <= 2 * pos->z)
	{
		x = 0;
		while (x <= 2 * pos->z)
		{
			dst = ft_sqrt((y - pos->z) * (y - pos->z)
						+ (x - pos->z) * (x - pos->z));
			if (fill && dst < pos->z + 0.5)
			{
				mlx_pixel_put(mlx[0], mlx[1], y + pos->y, x + pos->x, color);
			}
			else if (dst > pos->z - 0.5 && dst < pos->z + 0.5)
			{
				mlx_pixel_put(mlx[0], mlx[1], y + pos->y, x + pos->x, color);
			}
			x++;
		}
		y++;
	}
}
#include <math.h>
void	gradient(float frequency1, float frequency2, float frequency3,
		float phase1, float phase2, float phase3,
		float center, float width, float len, void **mlx)
{
	double red;
	double grn;
	double blu;

	for (int i = 0; i < len; ++i)
	{
		red = sin(frequency1*i + phase1) * width + center;
		grn = sin(frequency2*i + phase2) * width + center;
		blu = sin(frequency3*i + phase3) * width + center;

		for (int j = 0; j < len; ++j)
		{
			mlx_pixel_put(mlx[0], mlx[1], i, 600 + j, (int)red * 65536 + (int)grn * 256 + (int)blu);
		}
	}
}

int		get_color(int x, int y, float frequency1, float frequency2, float frequency3,
		float phase1, float phase2, float phase3,
		float center, float width, float len, void **mlx)
{
	double red;
	double grn;
	double blu;

	for (int i = 0; i < len; ++i)
	{
		red = sin(frequency1*i + phase1) * width + center;
		grn = sin(frequency2*i + phase2) * width + center;
		blu = sin(frequency3*i + phase3) * width + center;

		for (int j = 0; j < len; ++j)
		{
			if (i == x && j == y)
			{
				printf("%d\n", (int)red * 65536 + (int)grn * 256 + (int)blu);
				//exit (0);
				return ((int)red * 65536 + (int)grn * 256 + (int)blu);
			}
		}
	}
	return (0);
}
