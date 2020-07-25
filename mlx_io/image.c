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
	static char	*data = NULL;
	static int	pixels;
	void		**mlx;
	t_int_xy	window_size;

	if (!data)
	{
		mlx = get_mlx(NULL);
		data = mlx_get_data_addr(mlx[2], &pixels, &window_size.x, &window_size.y);
		window_size = get_window_size();
		pixels = window_size.x * window_size.y * 4;
	}
	ft_memset(data, 0, pixels);
}

void	pixel_put(int x, int y, unsigned color)
{
	static char	*data = NULL;
	static t_int_xy	window_size;
	void		**mlx;
	int		dummy;

	if (!data)
	{
		mlx = get_mlx(NULL);
		data = mlx_get_data_addr(mlx[2], &window_size.y, &window_size.x, &dummy);
		int a = window_size.x;
		window_size = get_window_size();
		window_size.x = a;
	}
	if (x * 4 >= window_size.x || y >= window_size.y || x < 0 || y < 0)
		return ;
	data[(y * window_size.x) + (x * 4) + 3] = color >> 4 * 6;
	data[(y * window_size.x) + (x * 4) + 2] = (color % 0x1000000) >> 4 * 4;
	data[(y * window_size.x) + (x * 4) + 1] = (color % 0x1000000) >> 4 * 2;
	data[(y * window_size.x) + (x * 4) + 0] = color % 0x1000000;
}

void	string_to_image(int x, int y, int color, char *str)
{
	static void **mlx = NULL;

	if (!mlx)
		mlx = get_mlx(NULL);
	mlx_string_put(mlx[0], mlx[1], x, y, color, str);
}
