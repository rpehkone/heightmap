/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/15 14:18:22 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "libft/libft.h"
# include "buttons/buttons.h"
# include <stdlib.h>
# include <fcntl.h>

typedef struct	s_xyz {
	double		x;
	double		y;
	double		z;
}				t_xyz;

int				handle_mouse_down(int button, int x, int y, void **mlx);
int				handle_mouse_up(int button, int x, int y, void **mlx);
int				handle_cursor(int x, int y, void **mlx);
int				handle_keyboard_down(int key);
int				handle_loop(void **mlx);
void			ft_printer(void **mlx, t_xyz *angle, t_xyz start, t_xyz stop);
void			image_pixel_put(void **mlx, int x, int y, int color);
void			print_line(t_xyz *start, t_xyz *stop, void **mlx);
int				buttons_main(int call, int x, int y, void **mlx);

int				fdf_main(int call, int x, int y, void **mlx);

int				fdf(int call, int x, int y, void **mlx);
t_xyz			*get_coord(int x, int y, t_xyz angle);
void			mlx_clear_image(void **mlx);
int				get_height(char *filename);
int				**make_map(char *filename);
int				check_file(char *filename);
int				get_width(char *filename);
void			init_image(void **mlx);
void			help_text(void **mlx);
void			ft_error(char *str);
float			ft_abs(float n);
void	mouse_control(int call, int *x, int *y, t_xyz *angle);

#endif
