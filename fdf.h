/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/14 15:04:20 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <stdio.h>
# include <fcntl.h>

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
int				handle_loop(void **mlx);
t_xyz			*get_coord(int x, int y, t_xyz angle);
int				buttons_main(int call, int x, int y, void **mlx);
void			image_pixel_put(void **mlx, int x, int y, int color);
void			mlx_clear_image(void **mlx);
void			init_image(void **mlx);
float			ft_abs(float n);
void			help_text(void **mlx);

#endif
