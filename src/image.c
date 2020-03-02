/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:04:17 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/02 17:00:28 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_clear_image(void **mlx)
{
	static char	*data = NULL;
	static int	width;
	int			a;
	int			b;

	if (!data)
	{
		data = mlx_get_data_addr(mlx[2], &width, &a, &b);
		width = get_width(NULL);
		width *= get_width(NULL) * 4;
	}
	ft_memset(data, 0, width);
}

void	image_pixel_put(void **mlx, int x, int y, unsigned color)
{
	static char	*data = NULL;
	static int	bpp = 0;
	static int	width = 0;
	static int	height = 0;
	static int	endian = 0;

	if (!width)
	{
		width = get_width(NULL);
		height = get_height(NULL);
	}
	if (x < 0 || y < 0)
		return ;
	if (x * 4 >= width || y >= height)
		return ;
	if (!data)
		data = mlx_get_data_addr(mlx[2], &bpp, &width, &endian);
	data[(y * width) + (x * 4) + 3] = color >> 4 * 6;
	data[(y * width) + (x * 4) + 2] = (color % 0x1000000) >> 4 * 4;
	data[(y * width) + (x * 4) + 1] = (color % 0x1000000) >> 4 * 2;
	data[(y * width) + (x * 4) + 0] = color % 0x1000000;
}
