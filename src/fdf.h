/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/04 17:50:01 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
#include <stdio.h>

typedef struct	s_xyz {
	double		x;
	double		y;
	double		z;
}				t_xyz;

typedef struct	s_button {
	int			x;
	int			y;
	int			size_x;
	int			size_y;
	int			b_color;
	int			bc_color;
	int			t_color;
	int			tc_color;
	int			type;
	int			edge;
	int			edge_color;
	int			stay_down;
	int			is_down;
	int			mouse_down;
	char		text[20];
}				t_button;

int				handle_loop(void **mlx);
int				handle_keyboard_down(int key, void **mlx);
int				handle_mouse_down(int button, int x, int y, void **mlx);
int				handle_mouse_up(int button, int x, int y, void **mlx);
int				handle_cursor(int x, int y, void **mlx);
void			image_pixel_put(void **mlx, int x, int y, unsigned color);
void			print_line(t_xyz start, t_xyz stop, t_xyz color, void **mlx);
int				fdf(int call, int x, int y, void **mlx);
void			mlx_clear_image(void **mlx);
int				get_height(char *filename);
t_xyz			*make_map(char *filename);
int				get_width(char *filename);
void			init_image(void **mlx);
void			help_text(void **mlx);
int				get_map_len(int n);
int				get_map_width(int n);
double			ft_abs(double n);

int				buttons_loop(int call, int x, int y, void **mlx);
int				button_1(int call, int x, int y, void **mlx);
int				button_2(int call, int x, int y, void **mlx);
int				button_3(int call, int x, int y, void **mlx);
int				button_4(int call, int x, int y, void **mlx);
int				button_5(int call, int x, int y, void **mlx);

int				handle_button(void **mlx, t_button b, int x, int y);
int				*get_settings(void);
int				gradient(void **mlx);
void			cycle_colors(t_xyz *color);
void			slider(void **mlx, int *n, int move);
t_xyz			get_cursor(int x, int y, void **mlx);
int		handle_keyboard_up(int key, void **mlx);

#endif
