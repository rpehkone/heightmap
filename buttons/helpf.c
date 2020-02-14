/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/14 13:58:24 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buttons.h"

void	put_gradient(void *gradient, int x, int y, int color)
{
	static char	*data = NULL;
	static int	bpp = 0;
	static int	width = 0;
	static int	endian = 0;

	if (x < 0 || y < 0)
		return ;
	if (x > 310 || y > 310)
		return ;
	if (!data)
		data = mlx_get_data_addr(gradient, &bpp, &width, &endian);
	data[(y * width) + (x * 4) + 3] = color >> 4 * 6;
	data[(y * width) + (x * 4) + 2] = (color % 0x1000000) >> 4 * 4;
	data[(y * width) + (x * 4) + 1] = (color % 0x1000000) >> 4 * 2;
	data[(y * width) + (x * 4) + 0] = color % 0x1000000;
}

void	make_gradient(void *image_ptr)
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
			put_gradient(image_ptr, i, j,
					(int)red * 65536 + (int)grn * 256 + (int)blu);
			j++;
		}
		i++;
	}
}

int		gradient(void **mlx)
{
	static void *gradient = NULL;

	if (!gradient)
	{
		gradient = mlx_new_image(mlx[0], 310, 310);
		make_gradient(gradient);
	}
	else
		mlx_put_image_to_window(mlx[0], mlx[1], gradient, 0, 40);
	return (1);
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
