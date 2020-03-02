/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:06:50 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/02 17:39:42 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_map(t_xyz *map, int fd, int width)
{
	int		x;
	int		x2;
	int		y;
	int		i;
	char	*line;

	x = 0;
	y = 0;
	while (get_next_line(fd, &line))
	{
		x2 = 0;
		i = 0;
		while (line[i])
		{
			map[x].x = 50 * x2;
			map[x].y = 50 * y;
			map[x].z = ft_atoi(&line[i]);
			while (line[i] && line[i] == ' ')
				i++;
			while (line[i] && line[i] != ' ')
				i++;
			x++;
			x2++;
		}
		y++;
		//while (x++ < width )
		//	map[y][x - 1] = 0;
		free(line);
	}
	width++;
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

int		get_map_len(int n)
{
	static int	len = 0;
	
	if (!n)
		return (len);
	len = n;
	return (0);
}

int		get_map_width(int n)
{
	static int	len = 0;
	
	if (!n)
		return (len);
	len = n;
	return (0);
}

t_xyz	*make_map(char *filename)
{
	int				width;
	int				height;
	static t_xyz		*map = NULL;
	int				fd;

	if (map)
		return (map);
	width = get_width(filename);
	height = get_height(filename);
	map = (t_xyz*)malloc(sizeof(t_xyz) * (width * height));
	fd = open(filename, O_RDONLY);
	get_map_len(width * height);
	get_map_width(width);
	set_map(map, fd, width);
	close(fd);
	return (map);
}
