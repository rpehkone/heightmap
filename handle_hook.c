/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:17:33 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/11 18:44:36 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		handle_loop(void **mlx)
{
	static int i = 0;

	i++;
	if (i < 200)
		return (0);
	i = 0;
	fdf(1, 0, 0, mlx);
	buttons_main(1, 0, 0, mlx);
	return (0);
}

int		handle_keyboard_down(int key)
{
	if (key == 53)
		exit(0);
	return (0);
}

int		handle_mouse_down(int button, int x, int y, void **mlx)
{
	fdf(4, button, 0, mlx);
	buttons_main(4, button, 0, mlx);
	(void)x;
	(void)y;
	return (0);
}

int		handle_mouse_up(int button, int x, int y, void **mlx)
{
	fdf(5, button, 0, mlx);
	buttons_main(5, button, 0, mlx);
	(void)x;
	(void)y;
	return (0);
}

int		handle_cursor(int x, int y, void **mlx)
{
	fdf(6, x, y, mlx);
	buttons_main(6, x, y, mlx);
	return (0);
}
