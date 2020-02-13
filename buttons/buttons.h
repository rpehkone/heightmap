/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/13 19:37:22 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUTTONS_H
# define BUTTONS_H
# include "mlx.h"
# include "../fdf.h"
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <math.h>
# include <stdio.h>

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

void			data(int call, int new_x, int new_y, void **mlx);
int				matrix(int call, int new_x, int new_y, void **mlx);
int				handle_button(void **mlx, t_button b, int x, int y);
int				asd(int call, int xd, int yd, void **mlx);
int				deal_key(int call, int c, int y, void **mlx);
void			gradient(void **mlx);
int				get_color(int x, int y);
int				button2_main(int call, int x, int y, void **mlx);

#endif
