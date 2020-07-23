/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 20:58:30 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/12 20:09:31 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_io.h"

int		loop_hook(void)
{
	fdf();
	return (0);
}

void	init_window(char *title)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	**mlx;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, get_width(NULL), get_height(NULL), title);
	img_ptr = mlx_new_image(mlx_ptr, get_width(NULL), get_height(NULL));
	if (!(mlx = (void **)malloc(sizeof(void *) * 3)))
		ft_error("malloc fail");
	mlx[0] = mlx_ptr;
	mlx[1] = win_ptr;
	mlx[2] = img_ptr;
	get_mlx(mlx);
	mlx_hook(win_ptr, 2, 0, handle_keyboard_down, mlx);
	mlx_hook(win_ptr, 3, 0, handle_keyboard_up, mlx);
	mlx_hook(win_ptr, 4, 0, handle_mouse_down, mlx);
	mlx_hook(win_ptr, 5, 0, handle_mouse_up, mlx);
	mlx_hook(win_ptr, 6, 0, handle_cursor, mlx);
	mlx_loop_hook(mlx_ptr, loop_hook, mlx);
	mlx_loop(mlx_ptr);
}
