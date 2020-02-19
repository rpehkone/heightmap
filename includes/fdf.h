/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/19 20:30:12 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <math.h>
# include <stdio.h>

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
	char		text[20];
}				t_button;

void			ft_printer(void **mlx, t_xyz *angle, t_xyz start, t_xyz stop);
int				handle_mouse_down(int button, int x, int y, void **mlx);
int				handle_mouse_up(int button, int x, int y, void **mlx);
void			mouse_control(int call, int *x, int *y, t_xyz *angle);
void			image_pixel_put(void **mlx, int x, int y, int color);
int				handle_button(void **mlx, t_button b, int x, int y);
int				matrix(int call, int new_x, int new_y, void **mlx);
void			print_line(t_xyz *start, t_xyz *stop, void **mlx);
int				buttons_main(int call, int x, int y, void **mlx);
int				button2_main(int call, int x, int y, void **mlx);
int				button3_main(int call, int x, int y, void **mlx);
void			data(int call, int new_x, int new_y, void **mlx);
int				draw_slider(int call, int x, int y, void **mlx);
int				fdf_main(int call, int x, int y, void **mlx);
int				deal_key(int call, int c, int y, void **mlx);
int				asd(int call, int xd, int yd, void **mlx);
int				fdf(int call, int x, int y, void **mlx);
int				handle_cursor(int x, int y, void **mlx);
t_xyz			*get_coord(int x, int y, t_xyz angle);
int				handle_keyboard_down(int key);
void			mlx_clear_image(void **mlx);
int				get_height(char *filename);
int				**make_map(char *filename);
void			check_file(char *filename);
int				get_width(char *filename);
int				get_color(int x, int y);
int				handle_loop(void **mlx);
void			init_image(void **mlx);
void			help_text(void **mlx);
int				gradient(void **mlx);
void			ft_error(char *str);
float			ft_abs(float n);

#endif
