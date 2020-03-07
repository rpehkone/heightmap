/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 19:06:50 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 20:42:32 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		if (width * 50 < 694)
			return (694);
		else if (width * 50 > 2000)
			return (2000);
		else
			return (width * 50);
	}
	open(filename, O_RDONLY);
	get_next_line(3, &line);
	while (line[i] && (width = width + 1))
	{
		while (line[i] && line[i] == ' ')
			i++;
		while (line[i] && line[i] != ' ')
			i++;
	}
	width = line[i - 1] == ' ' ? width - 1 : width;
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
	set_map(map, fd, width, get_map_len(0) / width / 2);
	close(fd);
	return (map_copy(map));
}
