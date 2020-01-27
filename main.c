/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/28 01:28:26 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		handle_keyboard_down(int key, void **mlx)
{
	if (key == 53)
		exit(0);
	return (0);
}

int		handle_mouse_down(int button, int x, int y, void **mlx)
{
	fdf(4, button, 0, mlx);
	return (0);
}

int		handle_mouse_up(int button, int x, int y, void **mlx)
{
	fdf(5, button, 0, mlx);
	return (0);
}

int		handle_cursor(int x, int y, void **mlx)
{
	fdf(6, x, y, mlx);
	return (0);
}

void	screen_size(int *height, int *width, char *filename)
{
	*width = get_width(filename) * 50;
	*height = get_height(filename) * 50;
	if (*height < 500)
		*height = 500;
	if (*width < 500)
		*width = 500;
	if (*width > 1000)
		*width = 1000;
	if (*height > 1000)
		*height = 1000;
}

int		main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	**mlx;
	int		width;
	int		height;

	if (argc != 2)
		exit(0);
	mlx_ptr = mlx_init();
	screen_size(&height, &width, argv[1]);
	win_ptr = mlx_new_window(mlx_ptr, width, height, "fdf");
	mlx = (void**)malloc(sizeof(void*) * 3);
	mlx[0] = mlx_ptr;
	mlx[1] = win_ptr;
	mlx[2] = argv[1];
	fdf(0, 0, 0, mlx);
	mlx_hook(win_ptr, 2, 0, handle_keyboard_down, mlx);
	mlx_hook(win_ptr, 4, 0, handle_mouse_down, mlx);
	mlx_hook(win_ptr, 5, 0, handle_mouse_up, mlx);
	mlx_hook(win_ptr, 6, 0, handle_cursor, mlx);
	mlx_loop(mlx_ptr);
	return (1);
}
