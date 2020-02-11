/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:06:50 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/11 22:10:34 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_map(int **map, int fd)
{
	int		x;
	int		y;
	int		i;
	char	*line;

	y = 0;
	while (get_next_line(fd, &line))
	{
		x = 0;
		i = 0;
		while (line[i])
		{
			map[y][x] = ft_atoi(&line[i]);
			while (line[i] && line[i] == ' ')
				i++;
			while (line[i] && line[i] != ' ')
				i++;
			x++;
		}
		y++;
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
		while ((line[i] && line[i] >= '0' && line[i] <= '9') || line[i] == '-')
			i++;
		while (line[i] && (line[i] < '0' || line[i] > '9') && line[i] != '-')
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
	map = (int**)malloc(sizeof(int*) * (height + 1));
	width = get_width(filename);
	while (i < height)
	{
		map[i] = (int*)malloc(sizeof(int) * (width + 1));
		i++;
	}
	fd = open(filename, O_RDONLY);
	close(fd);
	fd = open(filename, O_RDONLY);
	set_map(map, fd);
	close(fd);
	return (map);
}
