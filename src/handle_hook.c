/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:17:33 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/04 17:51:05 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		handle_loop(void **mlx)
{
	static int i = 0;

	i++;
	if (i < 100)
		return (0);
	i = 0;
	fdf(1, 0, 0, mlx);
	return (0);
}

t_xyz	get_cursor(int x, int y, void **mlx)
{
	static t_xyz	c = {.x = 0, .y = 0, .z = 0};

	if (mlx)
	{
		c.x = x;
		c.y = y;
	}
	return (c);
}

//int		is_down(int call, int key, void **mlx)
//{
		
//}

int		handle_keyboard_down(int key, void **mlx)
{
	if (key == 53)
		exit(0);
	//is_down(1, key, mlx);
	(void)mlx;
	return (0);
}

int		handle_keyboard_up(int key, void **mlx)
{
	//is_down(2, key, mlx);
	(void)key;
	(void)mlx;
	return (0);
}

int		handle_mouse_down(int button, int x, int y, void **mlx)
{
	//is_down(3, button, mlx);
	fdf(4, button, 0, mlx);
	(void)x;
	(void)y;
	return (0);
}

int		handle_mouse_up(int button, int x, int y, void **mlx)
{
	//is_down(4, key, mlx);
	fdf(5, button, 0, mlx);
	(void)x;
	(void)y;
	return (0);
}

int		handle_cursor(int x, int y, void **mlx)
{
	get_cursor(x, y, mlx);
	fdf(6, x, y, mlx);
	return (0);
}
