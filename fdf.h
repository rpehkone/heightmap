/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/30 19:17:54 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <stdio.h>
# include <fcntl.h>
# define BUFF_SIZE 42

typedef struct	s_xyz {
	double		x;
	double		y;
	double		z;
}				t_xyz;

int				handle_keyboard_down(int key, void **mlx);
void			ft_printer(void **mlx, t_xyz *angle, t_xyz start, t_xyz stop);
int				get_width(char *filename);
int				get_height(char *filename);
void			print_line(t_xyz *start, t_xyz *stop, void **mlx, unsigned color);
int				**make_map(char *filename);
int				fdf(int call, int x, int y, void **mlx);
int				get_next_line(const int fd, char **line);

#endif
