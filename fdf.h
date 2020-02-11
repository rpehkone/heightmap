/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/11 22:05:01 by rpehkone         ###   ########.fr       */
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
# define BUFF_SIZE 1

typedef struct	s_xyz {
	double		x;
	double		y;
	double		z;
}				t_xyz;

int				handle_keyboard_down(int key);
int				handle_mouse_down(int button, int x, int y, void **mlx);
int				handle_mouse_up(int button, int x, int y, void **mlx);
int				handle_cursor(int x, int y, void **mlx);
void			ft_printer(void **mlx, t_xyz *angle, t_xyz start, t_xyz stop);
int				get_width(char *filename);
int				get_height(char *filename);
void			print_line(t_xyz *start, t_xyz *stop, void **mlx);
int				**make_map(char *filename);
int				fdf(int call, int x, int y, void **mlx);
int				get_next_line(const int fd, char **line);
int				ft_atoi(const char *str);
int				handle_loop(void **mlx);
t_xyz			*get_coord(int x, int y, t_xyz angle);
int				buttons_main(int call, int x, int y, void **mlx);

#endif
