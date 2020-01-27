/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/09 21:46:11 by rpehkone         ###   ########.fr       */
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
	matrix(1, 0, 0, mlx);
	return (0);
}

int		handle_keyboard_down(int key, void **mlx)
{
	printf("kd k = %d\n", key);
	if (key == 53)
		exit(0);
	matrix(2, key, 0, mlx);
	return (0);
}

int		handle_keyboard_up(int key, void **mlx)
{
	printf("ky k = %d\n", key);
	matrix(3, key, 0, mlx);
	return (0);
}

int		handle_mouse_down(int button, int x, int y, void **mlx)
{
	printf("m_down b = %d\n", button);
	matrix(4, button, 0, mlx);
	return (0);
}

int		handle_mouse_up(int button, int x, int y, void **mlx)
{
	printf("m_up b = %d\n", button);
	matrix(5, button, 0, mlx);
	return (0);
}

int		handle_cursor(int x, int y, void **mlx)
{
	//printf("x = %d, y = %d\n", x, y);
	matrix(6, x, y, mlx);
	return (0);
}

int		main(int ac, char **av)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	**mlx;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "fdf");
	mlx = (void**)malloc(sizeof(void*) * 2);
	mlx[0] = mlx_ptr;
	mlx[1] = win_ptr;
	matrix(0, 0, 0, mlx);
	mlx_hook(win_ptr, 2, 0, handle_keyboard_down, mlx);
	mlx_hook(win_ptr, 3, 0, handle_keyboard_up, mlx);
	mlx_hook(win_ptr, 4, 0, handle_mouse_down, mlx);
	mlx_hook(win_ptr, 5, 0, handle_mouse_up, mlx);
	mlx_hook(win_ptr, 6, 0, handle_cursor, mlx);
	mlx_loop_hook(mlx_ptr, handle_loop, mlx);
	mlx_loop(mlx_ptr);
	return (1);
}
