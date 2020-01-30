/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:06:50 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/30 19:18:36 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		handle_keyboard_down(int key, void **mlx)
{
	if (key == 53)
		exit(0);
	return (0);
}

void	set_map(int **map, int fd, int width, int height)
{
	int		x;
	int		y;
	int		i;
	char	*line;

	y = height - 1;
	while (get_next_line(fd, &line))
	{
		x = width - 1;
		i = 0;
		while (line[i])
		{
			map[y][x] = atoi(&line[i]);
			while (line[i] && line[i] == ' ')
				i++;
			while (line[i] && line[i] != ' ')
				i++;
			x--;
		}
		y--;
		free(line);
	}
}

int		get_height(char *filename)
{
	char	*line;
	int		height;
	int		fd;

	height = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		free(line);
		height++;
	}
	close(fd);
	return (height);
}

int		get_width(char *filename)
{
	int		i;
	int		fd;
	char	*line;
	int		width;

	i = 0;
	width = 0;
	fd = open(filename, O_RDONLY);
	get_next_line(fd, &line);
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		while (line[i] && line[i] != ' ')
			i++;
		width++;
	}
	free(line);
	close(fd);
	return (width);
}

int		**make_map(char *filename)
{
	int		width;
	int		height;
	int		**map;
	int		i;
	int		fd;

	i = 0;
	height = get_height(filename);
	map = (int**)malloc(sizeof(int*) * (height));
	width = get_width(filename);
	while (i <= height)
	{
		map[i] = (int*)malloc(sizeof(int) * (width));
		i++;
	}
	fd = open(filename, O_RDONLY);
	set_map(map, fd, width, height);
	close(fd);
	return (map);
}
