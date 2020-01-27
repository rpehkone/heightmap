/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 19:06:52 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/12 19:26:18 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
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
			mlx_pixel_put(mlx[0], mlx[1], i, j, (int)red * 65536 + (int)grn * 256 + (int)blu);
			//mlx_pixel_put(mlx[0], mlx[1], i, j, (int)red * 65536);
			//mlx_pixel_put(mlx[0], mlx[1], i, j, (int)grn * 256);
			//mlx_pixel_put(mlx[0], mlx[1], i, j, (int)blu);
		}
		mlx_pixel_put(mlx[0], mlx[1], i, (int)red, 0xFFFFFF);
		mlx_pixel_put(mlx[0], mlx[1], i, (int)grn, 0xFFFFFF);
		mlx_pixel_put(mlx[0], mlx[1], i, (int)blu, 0xFFFFFF);
	}
}

int		matrix(int call, int new_x, int new_y, void **mlx)
{
	static int i = 0;
	static int j = 0;

	if (i < 128)
		i++;
	j += 5;
	gradient(.02,.02,.02,0,2,4, i, i - 1, 310, mlx);
	return (1);
}
