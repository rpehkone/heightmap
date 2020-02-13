/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:04:17 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/13 15:05:27 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	image_pixel_put(void **mlx, int x, int y, int color)
{
	static void *img_ptr = NULL;
	static char	*data = NULL;
	static int	bpp = 0;
	static int	width = 0;
	static int	endian = 0;

	if (!img_ptr)
		img_ptr = mlx_new_image(mlx[0], 1000, 1000);
	if (!data)
		data = mlx_get_data_addr(img_ptr, &bpp, &width, &endian);
	//impelemt check if pixel in correct line and on screen
	mlx[4] = img_ptr;
	data[(y * width) + (x * 4) + 3] = color >> 4 * 6;
	data[(y * width) + (x * 4) + 2] = (color % 0x1000000) >> 4 * 4;
	data[(y * width) + (x * 4) + 1] = (color % 0x1000000) >> 4 * 2;
	data[(y * width) + (x * 4) + 0] = color % 0x1000000;
}

void	mlx_clear_image(void **mlx, int width, int height)
{
	static char *data = NULL;

	if (!data)
		data = mlx_get_data_addr(mlx[4], NULL, NULL, NULL);
	ft_memset(data, 0, width * 4 * height);
}
