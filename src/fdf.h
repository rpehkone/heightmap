/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/12 18:41:04 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <stdio.h>

typedef struct	s_xyz {
	double	x;
	double	y;
	double	z;
}				xyz;

typedef struct	s_coords {
	int	x;
	int	y;
	int	z;
}				coords;

typedef struct	s_button {
	int		x;
	int		y;
	int		size_x;
	int		size_y;
	int		b_color;
	int		bc_color;
	int		t_color;
	int		tc_color;
	int		type;
	char	text[20];
}				button;

typedef struct	s_particle {
	int	x;
	int	y;
	int color;
	int charge;
}				particle;

void	print_line(xyz *start, xyz *stop, void **mlx, unsigned color);
void	putcircle(coords *pos, int fill, int color, void **mlx);
void	data(int call, int new_x, int new_y, void **mlx);
int		matrix(int call, int new_x, int new_y, void **mlx);
void	ft_point(void **mlx, particle p);
int		handle_button(void **mlx, button b, int x, int y);
int		asd(int call, int xd, int yd, void **mlx);
int		deal_key(int call, int c, int y, void **mlx);

void	gradient(float frequency1, float frequency2, float frequency3,
		float phase1, float phase2, float phase3,
		float center, float width, float len, void **mlx);

int		get_color(int x, int y, float frequency1, float frequency2, float frequency3,
		float phase1, float phase2, float phase3,
		float center, float width, float len, void **mlx);

//math
double	ft_abs(double x);
double	ft_sqrt(double n);
double	sinus(float x);
double	cosinus(float x);
void	rotateX(float theta, xyz *nodes);
void	rotateY(float theta, xyz *nodes);
void	rotateZ(float theta, xyz *nodes);

#endif
