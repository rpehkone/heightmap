/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 22:52:45 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/27 22:53:56 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*ft_join(char *s1, char *s2, char **as)
{
	char			*fresh;
	int				i;
	int				j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	if (!(fresh = (char*)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[j] != '\0')
		fresh[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j] != '\0')
		fresh[i++] = s2[j++];
	fresh[i] = '\0';
	if (as)
		free(*as);
	if (as)
		*as = NULL;
	return (fresh);
}

int		ft_has_newline(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

int		ft_set_value(char **line, char *tmp, size_t size)
{
	size_t line_size;

	line_size = 0;
	if (!tmp)
		return (0);
	if (!((*line) = (char*)malloc(sizeof(char) * (size + 1))))
		return (0);
	while (line_size < size)
	{
		(*line)[line_size] = tmp[line_size];
		line_size++;
	}
	(*line)[line_size] = '\0';
	return (1);
}

int		ft_make_line(char **line, char **tmp, int fd, int res)
{
	char	*tmp2;
	size_t	line_size;

	line_size = 0;
	while (tmp[fd][line_size] != '\n' && tmp[fd][line_size])
		line_size++;
	if (tmp[fd][line_size] == '\n')
	{
		ft_set_value(line, tmp[fd], line_size);
		tmp2 = ft_join(tmp[fd] + line_size + 1, NULL, &tmp[fd]);
		free(tmp[fd]);
		tmp[fd] = tmp2;
		return (1);
	}
	if (res == BUFF_SIZE)
		return (get_next_line(fd, line));
	*line = ft_join(tmp[fd], NULL, &tmp[fd]);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*tmp[4863];
	char		buff[BUFF_SIZE + 1];
	char		*tmp2;
	int			res;

	if (fd < 0 || !line)
		return (-1);
	while (0 < (res = read(fd, buff, BUFF_SIZE)))
	{
		buff[res] = '\0';
		if (tmp[fd] == NULL)
		{
			tmp[fd] = (char*)malloc(sizeof(char) * 2);
			tmp[fd][0] = 0;
			tmp[fd][1] = '\0';
		}
		tmp2 = ft_join(tmp[fd], buff, NULL);
		free(tmp[fd]);
		tmp[fd] = tmp2;
		if (ft_has_newline(buff))
			break ;
	}
	if ((res < 0) || (!res && (!tmp[fd] || !tmp[fd][0])))
		return (res);
	return (ft_make_line(line, tmp, fd, res));
}
