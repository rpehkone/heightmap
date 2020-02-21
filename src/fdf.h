/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/21 17:00:01 by rpehkone         ###   ########.fr       */
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

typedef struct	s_xyz {
	double		x;
	double		y;
	double		z;
}				t_xyz;

/*
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
int				handle_button(void **mlx, t_button b, int x, int y);
int				buttons_main(int call, int x, int y, void **mlx);
int				button2_main(int call, int x, int y, void **mlx);
int				button3_main(int call, int x, int y, void **mlx);
*/


int				handle_loop(void **mlx);
int				handle_keyboard_down(int key);
int				handle_mouse_down(int button, int x, int y, void **mlx);
int				handle_mouse_up(int button, int x, int y, void **mlx);
int				handle_cursor(int x, int y, void **mlx);
void			image_pixel_put(void **mlx, int x, int y, unsigned color);
void			print_line(t_xyz start, t_xyz stop, void **mlx);
int				fdf(int call, int x, int y, void **mlx);
void			mlx_clear_image(void **mlx);
int				get_height(char *filename);
int				**make_map(char *filename);
int				get_width(char *filename);
void			init_image(void **mlx);
void			help_text(void **mlx);

#endif
