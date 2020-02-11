/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/11 22:03:29 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buttons.h"

int			mouse_movement(int call, int x, int y)
{
	static int	m1_down = 0;
	static int	oldy = 0;
	static int	oldx = 0;
	static int	asd = 0;

	if (asd == 1)
	{
		oldx = x;
		oldy = y;
		asd = 0;
	}
	if (call == 4 && x == 1)
	{
		m1_down = 1;
		asd = 1;
	}
	if (call == 5 && x == 1)
		m1_down = 0;
	if (call == 6 && m1_down == 1)
	{
		oldx = x;
		oldy = y;
	}
	return (asd);
}

t_button	*set_b_color(void)
{
	static t_button	b_color = {.text = "Color"};

	b_color.x = 0;
	b_color.y = 0;
	b_color.size_x = 75;
	b_color.size_y = 40;
	b_color.b_color = 0x000000;
	b_color.bc_color = 0xFFFFFF;
	b_color.t_color = 0xFF0000;
	b_color.tc_color = 0xFF0000;
	b_color.type = 0;
	return (&b_color);
}

int			buttons_main(int call, int x, int y, void **mlx)
{
	static t_button	*b_color = NULL;
	static int		oldy = 0;
	static int		oldx = 0;
	static int		grd = 0;
	int				i;

	if (!b_color)
		b_color = set_b_color();
	if (call == 6)
		oldx = x;
	if (call == 6)
		oldy = y;
	mouse_movement(call, x, y);
	mlx_clear_window(mlx[0], mlx[1]);
	if (grd)
	{
		gradient(mlx);
		if (call == 4 && x == 1)
			if ((i = get_color(oldx, oldy - 60)))
				*(int*)mlx[3] = i;
	}
	if (handle_button(mlx, *b_color, oldx, oldy))
		if (call == 4 && x == 1)
			grd = grd ? 0 : 1;
	return (0);
}
