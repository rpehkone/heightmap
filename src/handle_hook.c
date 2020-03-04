/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:17:33 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/04 21:11:57 by rpehkone         ###   ########.fr       */
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
	fdf(mlx);
//	(void)mlx;
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

int		is_key_down(int call, int key)
{
	static int	*keyb = NULL;
	int			i;

	if (!keyb)
	{
		i = 0;
		keyb = (int*)malloc(sizeof(int) * 1000);
		while (i < 1000)
		{
			keyb[i] = 0;
			i++;
		}
	}
	if (call == 0)
		return (keyb[key]);
	else if (call == 1)
		keyb[key] = 1;
	else if (call == 2)
		keyb[key] = 0;
	return (0);
}

int		is_mouse_down(int call, int button)
{
	static int	*mouse = NULL;
	int			i;

	if (!mouse)
	{
		i = 0;
		mouse = (int*)malloc(sizeof(int) * 6);
		while (i < 6)
		{
			mouse[i] = 0;
			i++;
		}
	}
	if (call == 0)
		return (mouse[button]);
	else if (call == 1)
		mouse[button] = 1;
	else if (call == 2)
		mouse[button] = 0;
	return (0);
}

int		handle_keyboard_down(int key, void **mlx)
{
	if (key == 53)
	{
		exit(0);
	}
	is_key_down(1, key);
	fdf(mlx);
	return (0);
}

int		handle_keyboard_up(int key, void **mlx)
{
	is_key_down(2, key);
	fdf(mlx);
	return (0);
}

int		handle_mouse_down(int button, int x, int y, void **mlx)
{
	is_mouse_down(1, button);
	get_cursor(x, y, mlx);
	fdf(mlx);
	if (button == 4 || button == 5)
		is_mouse_down(2, button);
	return (0);
}

int		handle_mouse_up(int button, int x, int y, void **mlx)
{
	is_mouse_down(2, button);
	get_cursor(x, y, mlx);
	fdf(mlx);
	return (0);
}

int		handle_cursor(int x, int y, void **mlx)
{
	get_cursor(x, y, mlx);
	fdf(mlx);
	return (0);
}
