/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/05 16:28:38 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int		set_gradient_color(int x, int y)
{
	double	red;
	double	grn;
	double	blu;
	int		i;
	int		j;

	i = 0;
	j = 0;
	y += 20;
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

int		gradient(void **mlx)
{
	static void *gradient = NULL;
	t_xyz		cursor;

	if (!gradient)
	{
		gradient = mlx_new_image(mlx[0], 310, 310);
		make_gradient(gradient);
	}
	else
		mlx_put_image_to_window(mlx[0], mlx[1], gradient, 0, 31);
	if (is_mouse_down(0, 1))
	{
		cursor = get_cursor(0, 0, NULL);
		get_color(set_gradient_color(cursor.x, cursor.y));
	}
	return (1);
}

void	cycle_colors(t_xyz *color)
{
	static int	i = 0;
	static int	old = 0;
	double		red;
	double		grn;
	double		blu;

	if (color->x != old && color->x != 0xFFFFFF)
		while (color->x != old)
		{
			if (i > 310)
				i = 0;
			red = sin(0.02 * i + 0) * 127 + 128;
			grn = sin(0.02 * i + 2) * 127 + 128;
			blu = sin(0.02 * i + 4) * 127 + 128;
			old = ((int)red * 65536 + (int)grn * 256 + (int)blu);
			i++;
		}
	if (i > 310)
		i = 0;
	red = sin(0.02 * i + 0) * 127 + 128;
	grn = sin(0.02 * i + 2) * 127 + 128;
	blu = sin(0.02 * i + 4) * 127 + 128;
	old = ((int)red * 65536 + (int)grn * 256 + (int)blu);
	color->x = old;
	i++;
}
