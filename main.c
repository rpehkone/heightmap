/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/14 12:50:05 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_xyz	*get_coord(int x, int y, t_xyz angle)
{
	static t_xyz	coord;

	coord.x = x;
	coord.y = y;
	coord.z = angle.z;
	return (&coord);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(1, &(*str), 1);
		str++;
	}
}
//add libft

void	ft_error(char *str)
{
	if (str)
	{
		ft_putstr("usage: ");
		ft_putstr(str);
		ft_putstr(" [source_file]\n");
	}
	else
	{
		ft_putstr("error\n");
	}
	exit(0);
}

void	main2(char *argv, int width)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	**mlx;
	int		height;
	float	height_multiplier;

	height_multiplier = .1;
	mlx_ptr = mlx_init();
	screen_size(&height, &width, argv);
	win_ptr = mlx_new_window(mlx_ptr, width, height, "fdf");
	mlx = (void**)malloc(sizeof(void*) * 8);
	mlx[0] = mlx_ptr;
	mlx[1] = win_ptr;
	mlx[2] = argv;
	mlx[5] = &width;
	mlx[6] = &height;
	mlx[7] = &height_multiplier;
	init_image(mlx);
	mlx_hook(win_ptr, 2, 0, handle_keyboard_down, mlx);
	mlx_hook(win_ptr, 4, 0, handle_mouse_down, mlx);
	mlx_hook(win_ptr, 5, 0, handle_mouse_up, mlx);
	mlx_hook(win_ptr, 6, 0, handle_cursor, mlx);
	mlx_loop_hook(mlx_ptr, handle_loop, mlx);
	mlx_loop(mlx_ptr);
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		ft_error(argv[0]);
	if (open(argv[1], O_RDONLY) < 2)
		ft_error(NULL);
	main2(argv[1], 0);
	return (1);
}
