/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:06:50 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/19 18:19:23 by rpehkone         ###   ########.fr       */
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
	char		*line;
	int			fd;
	static int	height = 0;

	if (height)
		return (height);
	fd = open(filename, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		free(line);
		height++;
	}
	close(fd);
	return (height);
}

void	check_file(char *filename)
{
	int		i;
	int		fd;
	char	*line;
	char	c;

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

int		get_width(char *filename)
{
	int			i;
	int			j;
	int			fd;
	char		*line;
	static int	width = 0;

	if (width)
		return (width);
	i = 0;
	j = 0;
	fd = open(filename, O_RDONLY);
	get_next_line(fd, &line);
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		while (line[i] && line[i] != ' ')
			i++;
		j++;
	}
	free(line);
	width = j;
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
