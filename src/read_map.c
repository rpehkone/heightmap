/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:06:50 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/21 16:42:50 by rpehkone         ###   ########.fr       */
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

	if (height != 0)
	{
		if (height * 50 < 500)
			return (500);
		else if (height * 50 > 1000)
			return (1000);
		else
			return (height * 50);
	}
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
	int			i;
	char		*line;
	static int	width = 0;

	if (!(i = 0) && width != 0)
	{
		if (width * 50 < 500)
			return (500);
		else if (width * 50 > 1000)
			return (1000);
		else
			return (width * 50);
	}
	open(filename, O_RDONLY);
	get_next_line(3, &line);
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		while (line[i] && line[i] != ' ')
			i++;
		width++;
	}
	free(line);
	return (width);
}

int		**make_map(char *filename)
{
	int				width;
	int				height;
	static int		**map = NULL;
	int				i;
	int				fd;

	if (map)
		return (map);
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
