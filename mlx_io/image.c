/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:04:17 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/12 20:03:16 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_io.h"

void	update_image(void)
{
	static void **mlx = NULL;

	if (!mlx)
		mlx = get_mlx(NULL);
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
}

void	clear_image(void)
{
	static void	**mlx = NULL;
	static char	*data = NULL;
	static int	pixels;
	static int	width = 0;
	static int	height = 0;
	int			a;
	int			b;

	if (!data)
	{
		width = get_width(NULL);
		height = get_height(NULL);
		mlx = get_mlx(NULL);
		data = mlx_get_data_addr(mlx[2], &pixels, &a, &b);
		pixels = width * height * 4;
	}
	ft_memset(data, 0, pixels);
}

void	**get_mlx(void **mlx)
{
	static void	**mlx_save = NULL;

	if (!mlx)
		return (mlx_save);
	mlx_save = mlx;
	return (mlx_save);
}
//move get width to mlx io
void	pixel_put(int x, int y, unsigned color)
{
	static void	**mlx = NULL;
	static char	*data = NULL;
	static int	bpp = 0;
	static int	width = 0;
	static int	height = 0;
	static int	endian = 0;

	if (!mlx)
		mlx = get_mlx(NULL);
	if (!data)
	{
		data = mlx_get_data_addr(mlx[2], &bpp, &width, &endian);
		height = get_height(NULL);
		//remove bpp
	}
	if (x * 4 >= width || y >= height || x < 0 || y < 0)
		return ;
	data[(y * width) + (x * 4) + 3] = color >> 4 * 6;
	data[(y * width) + (x * 4) + 2] = (color % 0x1000000) >> 4 * 4;
	data[(y * width) + (x * 4) + 1] = (color % 0x1000000) >> 4 * 2;
	data[(y * width) + (x * 4) + 0] = color % 0x1000000;
}
