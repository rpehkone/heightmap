/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 18:37:25 by rpehkone         ###   ########.fr       */
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
	if (is_mouse_down(0, 1) && get_settings(0, NULL) &&
		!get_settings(4, NULL) && !get_settings(2, NULL))
	{
		rotate_y((float)0.01 * (x - cursor.x), nodes, amount);
		rotate_x(-1 * (float)0.01 * (y - cursor.y), nodes, amount);
	}
	x = cursor.x;
	y = cursor.y;
}

int		get_settings(int i, t_button *all_b)
{
	static t_button	*st = NULL;

	if (!st && all_b)
	{
		st = all_b;
		return (0);
	}
	if (i < 0)
	{
		st[i * -1].is_down = 0;
	}
	return (st[i].is_down);
}

void	reset(void **mlx)
{
	int i;

	i = 1;
	while (i <= 9)
	{
		get_settings(-1 * i, NULL);
		i++;
	}
	get_color(0xFFFFFF);
	move_center(NULL, NULL, 1, mlx);
	add_perspective(NULL, NULL, 1, NULL);
	draw(NULL, 0, 1, NULL);
	slider_button(NULL, 0, 1);
	center_image(NULL, NULL, 1, NULL);
}

int		matrix(void **mlx)
{
	static t_xyz	*nodes = NULL;
	static int		amount = 0;

	if (!nodes || get_settings(8, NULL))
	{
		nodes = make_map(NULL, 0);
		rotate_x(-1, nodes, get_map_len(0));
		rotate_y(1, nodes, get_map_len(0));
		reset(mlx);
	}
	if (!amount)
		amount = get_map_len(0);
	mlx_clear_window(mlx[0], mlx[1]);
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[2], 0, 0);
	mlx_clear_image(mlx);
	matrix_transform(nodes, amount);
	draw(nodes, amount, 0, mlx);
	return (0);
}

int		fdf(void **mlx)
{
	matrix(mlx);
	buttons_loop(mlx);
	help_text(mlx);
	return (0);
}
