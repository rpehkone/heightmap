/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:17:33 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/04 22:35:25 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
