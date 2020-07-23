/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_io.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/12 19:33:22 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_IO_H
# define MLX_IO_H
# include "mlx.h"
# include "libft.h"

//t_ivec2
typedef struct	s_int_xy {
	int			x;
	int			y;
}				t_int_xy;

int				handle_keyboard_down(int key);
int				handle_keyboard_up(int key);
int				handle_mouse_down(int button, int x, int y);
int				handle_mouse_up(int button, int x, int y);
int				handle_cursor(int x, int y);
int				loop_hook(void);
void			**get_mlx(void **mlx);

t_int_xy		set_cursor(int call, int x, int y);
int				set_mouse(int call, int button);
int				set_key(int call, int key);
t_int_xy		get_cursor(void);
int				is_key_down(int key);
int				is_mouse_down(int button);

void			pixel_put(int x, int y, unsigned color);
void			clear_image(void);
void			update_image(void);
void			init_image(void **mlx);
void			ft_error(char *str);

void			fdf(void);
void		win_init(char *filename);
void		button_layer(void);
int				get_height(char *filename);
int				get_width(char *filename);
#endif
