/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:06:50 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/14 15:46:23 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_map(int **map, int fd, int width)
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
		while (x++ < width)
			map[y][x - 1] = 0;
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
	int		j;
	int		fd;
	char	*lne;
	int		width;

	i = 0;
	width = 0;
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &lne))
	{
		j = 0;
		while (lne[i])
		{
			while ((lne[i] && lne[i] >= '0' && lne[i] <= '9') || lne[i] == '-')
				i++;
			while (lne[i] && (lne[i] < '0' || lne[i] > '9') && lne[i] != '-')
				i++;
			j++;
		}
		if (j > width)
			width = j;
		free(lne);
	}
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
	set_map(map, fd, width);
	close(fd);
	return (map);
}
