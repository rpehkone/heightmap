/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:06:50 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 15:50:41 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_map(t_xyz *map, int fd, int width)
{
	int		x;
	int		y;
	int		i;
	char	*line;
	int		height;

	x = 0;
	y = 0;
	height = get_map_len(0) / width / 2;
	while (!(i = 0) && get_next_line(fd, &line))
	{
		while (line[i])
		{
			map[x].x = 50 * ((x - (y * width)) - width / 2);
			map[x].y = 50 * (y - height);
			map[x].z = -10 * ft_atoi(&line[i]);
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
	char		*line;
	int			fd;
	static int	height = 0;

	if (height != 0)
	{
		if (height * 50 < 500)
			return (500);
		else if (height * 50 > 1200)
			return (1200);
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
		if (width * 50 < 862)
			return (862);
		else if (width * 50 > 2000)
			return (2000);
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

t_xyz	*map_copy(t_xyz *map)
{
	static t_xyz	*map_copy = NULL;
	int				len;
	int				i;

	len = get_map_len(0);
	if (!map_copy)
		if (!(map_copy = (t_xyz*)malloc(sizeof(t_xyz) * len)))
			ft_error(NULL);
	i = 0;
	while (i < len)
	{
		map_copy[i] = map[i];
		i++;
	}
	return (map_copy);
}

t_xyz	*make_map(char *filename, int which)
{
	int				width;
	int				height;
	static t_xyz	*map = NULL;
	int				fd;

	if (map)
	{
		if (which)
			return (map);
		return (map_copy(map));
	}
	width = get_width(filename);
	height = get_height(filename);
	if (!(map = (t_xyz*)malloc(sizeof(t_xyz) * (width * height))))
		ft_error(NULL);
	fd = open(filename, O_RDONLY);
	get_map_len(width * height);
	get_map_width(width);
	set_map(map, fd, width);
	close(fd);
	return (map_copy(map));
}
