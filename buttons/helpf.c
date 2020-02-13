/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/13 13:51:29 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buttons.h"

void	gradient(void **mlx)
{
	double	red;
	double	grn;
	double	blu;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 310)
	{
		red = sin(0.02 * i + 0) * 127 + 128;
		grn = sin(0.02 * i + 2) * 127 + 128;
		blu = sin(0.02 * i + 4) * 127 + 128;
		j = 0;
		while (j < 310)
		{
			image_pixel_put(mlx, i, 60 + j,
					(int)red * 65536 + (int)grn * 256 + (int)blu);
			j++;
		}
		i++;
	}
}

int		get_color(int x, int y)
{
	double	red;
	double	grn;
	double	blu;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < 310)
	{
		red = sin(0.02 * i + 0) * 127 + 128;
		grn = sin(0.02 * i + 2) * 127 + 128;
		blu = sin(0.02 * i + 4) * 127 + 128;
		j = 0;
		while (j < 310)
		{
			if (i == x && j == y)
				return ((int)red * 65536 + (int)grn * 256 + (int)blu);
			j++;
		}
		i++;
	}
	return (0);
}
