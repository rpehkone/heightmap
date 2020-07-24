/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/12 20:03:32 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_errors(char *filename)
{
	int		i;
	int		fd;
	char	*line;
	char	c;

	fd = open(filename, O_RDONLY);
	if (fd < 2)
		ft_error(NULL);
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

void	ft_error(char *error)
{
	if (error)
		ft_putstr(error);
	else
		ft_putstr("error");
	ft_putchar('\n');
	exit(0);
}

int		main(int argc, char **argv)
{
	int	i;

	if (argc != 2)
	{
		ft_putstr("usage: ");
		ft_putstr(argv[0]);
		ft_putstr(" source_file\n");
	}
	else
	{
		check_errors(argv[1]);
		make_map(argv[1], 0);
		button_layer();
		i = ft_strlen(argv[1]);
		while (i >= 0 && argv[1][i] != '/')
			i--;
		init_window(&argv[1][i + 1]);
	}
	return (0);
}
