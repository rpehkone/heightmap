/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/19 20:26:24 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			mouse_movement(int call, int x)
{
	static int	m1_down = 0;

	if (call == 4 && x == 1)
		m1_down = 1;
	if (call == 5 && x == 1)
		m1_down = 0;
	return (m1_down);
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
	b_color.t_color = 0xFFFFFF;
	b_color.tc_color = 0x000000;
	b_color.type = 0;
	return (&b_color);
}

int			button1_main(int call, int x, int y, void **mlx)
{
	static t_button	*b_color = NULL;
	static int		oldy = 0;
	static int		oldx = 0;
	static int		grd = 0;
	int				i;

	grd = call == 10 ? 0 : grd;
	b_color = !b_color ? set_b_color() : b_color;
	oldx = call == 6 ? x : oldx;
	oldy = call == 6 ? y : oldy;
	if (grd && gradient(mlx) && call == 4)
	{
		if ((i = get_color(oldx, oldy - 60)))
			*(int*)mlx[3] = i;
		else if (!(grd = 0) && !fdf_main(6, oldx, oldy, mlx) &&
		!fdf_main(5, x, 0, mlx))
			return (0);
	}
	b_color->b_color = grd ? 0xFFFFFF : 0;
	b_color->t_color = !grd ? 0xFFFFFF : 0;
	if ((y = handle_button(mlx, *b_color, oldx, oldy)) &&
			(b_color->tc_color = mouse_movement(call, x) ? 0xFFFFFF : 0))
		if (call == 4 && x == 1)
			grd = grd ? 0 : 1;
	return (grd + y);
}

int			buttons_main(int call, int x, int y, void **mlx)
{
	int res;

	res = button1_main(call, x, y, mlx);
	res += button2_main(call, x, y, mlx);
	res += button3_main(call, x, y, mlx);
	return (res);
}
