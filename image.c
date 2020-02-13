/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:04:17 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/13 15:54:42 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_clear_image(void **mlx)
{
	static char	*data = NULL;
	static int	width;
	static int	height;
	int			asd;

	if (!data)
	{
		data = mlx_get_data_addr(mlx[4], &width, &height, &asd);
		width = *(int*)mlx[5];
		height = *(int*)mlx[6];
	}
	ft_memset(data, 0, width * 4 * height);
}

void	image_pixel_put(void **mlx, int x, int y, int color)
{
	static char	*data = NULL;
	static int	bpp = 0;
	static int	width = 0;
	static int	endian = 0;

	if (x < 0 || y < 0)
		return ;
	if (x >= *(int*)mlx[5] || y >= *(int*)mlx[6])
		return ;
	if (!data)
		data = mlx_get_data_addr(mlx[4], &bpp, &width, &endian);
	data[(y * width) + (x * 4) + 3] = color >> 4 * 6;
	data[(y * width) + (x * 4) + 2] = (color % 0x1000000) >> 4 * 4;
	data[(y * width) + (x * 4) + 1] = (color % 0x1000000) >> 4 * 2;
	data[(y * width) + (x * 4) + 0] = color % 0x1000000;
}

void	init_image(void **mlx)
{
	static void *img_ptr = NULL;

	if (!img_ptr)
	{
		img_ptr = mlx_new_image(mlx[0], *(int*)mlx[5], *(int*)mlx[6]);
		mlx[4] = img_ptr;
	}
}
