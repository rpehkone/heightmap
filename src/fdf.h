/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 20:38:09 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "mlx_io.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>

# include <stdio.h>

//rename the structs to s_int3 ... and so on
typedef struct	s_xyz {
	double		x;
	double		y;
	double		z;
}				t_xyz;
//add defines for setting numbers
typedef struct	s_button {
	int			x;
	int			y;
	int			size_x;
	int			size_y;
	int			b_color;
	int			bc_color;
	int			bd_color;
	int			t_color;
	int			tc_color;
	int			td_color;
	int			edge;
	int			edge_color;
	int			edgec_color;
	int			stay_down;
	int			is_down;
	int			mouse_down;
	char		*text;
}				t_button;

void		text_layer(void);
void		button_layer(void);
void		print_button(t_button *b);

int		get_settings(int i, t_button *st);
t_button	*get_buttons(t_button *b);


void	init_window(char *title);

//*
void			print_line(t_xyz start, t_xyz stop, t_xyz color, void **mlx);
int				get_height(char *filename);
t_xyz			*make_map(char *filename, int which);
int				get_width(char *filename);
int				get_map_len(int n);
int				get_map_width(int n);
double			ft_abs(double n);
int				gradient(void **mlx);
void			cycle_colors(t_xyz *color);
void			slider(void **mlx, int *n);
void			ft_error(char *str);
void			rotate_x(float angle, t_xyz *nodes, int amount);
void			rotate_y(float angle, t_xyz *nodes, int amount);
void			rotate_z(float angle, t_xyz *nodes, int amount);
void			add_perspective(t_xyz *start, t_xyz *stop,
					int reset, void **mlx);
t_xyz			get_color(int set);
void			draw(t_xyz *nodes, int map_len, int reset);
t_xyz			add_color_height(t_xyz color);
int				save_coord(int start_i, int stop_i, int which);
void			move_center(t_xyz *start, t_xyz *stop, int reset, void **mlx);
void			print_edge(t_xyz start, t_xyz stop, t_button *b);
void			slider_button(void **mlx, int *n, int reset);
void			center_image(t_xyz *start, t_xyz *stop, int reset, void **mlx);
void			set_map(t_xyz *map, int fd, int width, int height);
//*/
#endif
