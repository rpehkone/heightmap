/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/05 16:45:03 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	matrix_transform(t_xyz *nodes, int amount)
{
	static int	x = 0;
	static int	y = 0;
	t_xyz		cursor;

	cursor = get_cursor(0, 0, NULL);
	if (get_settings(3, NULL))
		rotate_y((float)0.01, nodes, amount);
	if (get_settings(0, NULL) && is_mouse_down(0, 1))
		rotate_y(-1 * (float)0.01 * (x - cursor.x), nodes, amount);
	if (get_settings(0, NULL) && is_mouse_down(0, 1))
		rotate_x((float)0.01 * (y - cursor.y), nodes, amount);
	x = cursor.x;
	y = cursor.y;
}

int		matrix(void **mlx)
{
	static t_xyz	*nodes = NULL;
	static int		amount = 0;

	if (!nodes)
		nodes = make_map(NULL);
	if (!amount)
		amount = get_map_len(0);
	mlx_clear_window(mlx[0], mlx[1]);
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
	mlx_clear_image(mlx);
	matrix_transform(nodes, amount);
	draw(nodes, amount, mlx);
	return (0);
}

void	fps(void **mlx)
{
	struct timeval	time;
	static long		s = 0;
	static int		i = 0;
	static int		fps = 0;
	static int		height = 0;
	char			*str;

	i++;
	if (!height)
		height = get_height(NULL);
	gettimeofday(&time, NULL);
	str = ft_itoa(fps);
	if (get_settings(8, NULL))
		mlx_string_put(mlx[0], mlx[1], 10,
		height - 30, 0xFFFF00, str);
	free(str);
	if (s != time.tv_sec)
	{
		s = time.tv_sec;
		fps = i;
		i = 0;
	}
}

void		reset(void)
{
	int i;

	i = 1;
	while (i <= 9)
	{
		get_settings(-1 * i, NULL);
		get_color(0xFFFFFF);
		i++;
	}
}

int		fdf(void **mlx)
{
	matrix(mlx);
	buttons_loop(mlx);
	help_text(mlx);
	fps(mlx);
	if (get_settings(9, NULL))
		reset();
	return (0);
}
