/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/05 01:29:35 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	check_file(char *filename)
{
	int		i;
	int		fd;
	char	*line;
	char	c;

	if (open(filename, O_RDONLY) < 2)
		ft_error(NULL);
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (!(i = 0) && !line)
			ft_error(NULL);
		while (line[i])
		{
			c = line[i];
			if (!(c >= '0' && c <= '9') && (c != ' ' && c != '-' && c != '+' &&
			c != 'a' && c != 'b' && c != 'c' && c != 'd' && c != 'e' &&
			c != 'f' && c != 'A' && c != 'B' && c != 'C' && c != 'D' &&
			c != 'E' && c != 'F' && c != 'x' && c != '\t' && c != ','))
				ft_error(NULL);
			i++;
		}
		free(line);
	}
}

void	win_init(char *filename, void **mlx_ptr, void **win_ptr, void **img_ptr)
{
	int		width;
	int		height;
	int		i;

	width = get_width(filename);
	height = get_height(filename);
	if (!width || !height)
		ft_error(NULL);
	if ((width == 1 && height == 1) || (width > 5 && height == 1))
		ft_error(NULL);
	if (width == 1 && height > 5)
		ft_error(NULL);
	if (height < 500)
		height = 500;
	if (width < 500)
		width = 500;
	if (width > 1000)
		width = 1000;
	if (height > 1000)
		height = 1000;
	i = ft_strlen(filename);
	while (i > 0 && filename[i] != '/')
		i--;
	*win_ptr = mlx_new_window(*mlx_ptr, width, height, &filename[i + 1]);
	*img_ptr = mlx_new_image(*mlx_ptr, width, height);
}

int		main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	void	**mlx;

	if (argc != 2)
		ft_error(argv[0]);
	make_map(argv[1]);
	check_file(argv[1]);
	mlx_ptr = mlx_init();
	win_init(argv[1], &mlx_ptr, &win_ptr, &img_ptr);
	if (!(mlx = (void **)malloc(sizeof(void *) * 3)))
		ft_error(NULL);
	mlx[0] = mlx_ptr;
	mlx[1] = win_ptr;
	mlx[2] = img_ptr;
	mlx_hook(win_ptr, 2, 0, handle_keyboard_down, mlx);
	mlx_hook(win_ptr, 3, 0, handle_keyboard_up, mlx);
	mlx_hook(win_ptr, 4, 0, handle_mouse_down, mlx);
	mlx_hook(win_ptr, 5, 0, handle_mouse_up, mlx);
	mlx_hook(win_ptr, 6, 0, handle_cursor, mlx);
	mlx_loop_hook(mlx_ptr, fdf, mlx);
	mlx_loop(mlx_ptr);
	return (0);
}
