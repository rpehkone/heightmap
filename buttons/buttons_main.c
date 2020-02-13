/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/13 19:20:43 by rpehkone         ###   ########.fr       */
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
	return (m1_down);
}

void	cycle_colors(void **mlx)
{
	static int	i = 0;
	static int	old;
	double		red;
	double		grn;
	double		blu;

	if (i > 310)
		i = 0;
	red = sin(0.02 * i + 0) * 127 + 128;
	grn = sin(0.02 * i + 2) * 127 + 128;
	blu = sin(0.02 * i + 4) * 127 + 128;
	old = ((int)red * 65536 + (int)grn * 256 + (int)blu);
	*(int*)mlx[3] = old;
	i++;
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
	static int		i;

	if (call == 10)
	{
		grd = 0;
		return (0);
	}
	if (!b_color)
		b_color = set_b_color();
	oldx = call == 6 ? x : oldx;
	oldy = call == 6 ? y : oldy;
	if (grd)
	{
		gradient(mlx);
		if (call == 4 && x == 1)
			if ((i = get_color(oldx, oldy - 60)))
				*(int*)mlx[3] = i;
	}
	i = mouse_movement(call, x, y);
	b_color->b_color = grd ? 0xFFFFFF : 0;
	b_color->t_color = !grd ? 0xFFFFFF : 0;
	if (handle_button(mlx, *b_color, oldx, oldy) &&
			(b_color->tc_color = i ? 0xFFFFFF : 0))
		if (call == 4 && x == 1)
			grd = grd ? 0 : 1;
	return (grd);
}

t_button	*set_b_cycle(void)
{
	static t_button	b = {.text = "Cycle"};

	b.x = 75;
	b.y = 0;
	b.size_x = 75;
	b.size_y = 40;
	b.b_color = 0x000000;
	b.bc_color = 0xFFFFFF;
	b.t_color = 0xFFFFFF;
	b.tc_color = 0x000000;
	b.type = 0;
	return (&b);
}

void		edit_button2(t_button *b_cycle, int cycle, void **mlx)
{
	if (cycle)
	{
		b_cycle->b_color = *(int*)mlx[3];
		b_cycle->bc_color = *(int*)mlx[3];
		b_cycle->t_color = 0;
		b_cycle->tc_color = 0xFFFFFF;
		cycle_colors(mlx);
	}
	else
	{
		b_cycle->b_color = 0;
		b_cycle->bc_color = 0xFFFFFF;
		b_cycle->t_color = 0xFFFFFF;
		b_cycle->tc_color = 0;
	}
}

int			button2_main(int call, int x, int y, void **mlx)
{
	static t_button	*b_cycle = NULL;
	static int		oldy = 0;
	static int		oldx = 0;
	static int		cycle = 0;

	if (call == 10)
		cycle = 0;
	oldx = call == 6 ? x : oldx;
	oldy = call == 6 ? y : oldy;
	if (!b_cycle)
		b_cycle = set_b_cycle();
	if (handle_button(mlx, *b_cycle, oldx, oldy) && call == 4 && x == 1)
		cycle = cycle ? 0 : 1;
	b_cycle->tc_color = 0;
	edit_button2(b_cycle, cycle, mlx);
	return (cycle);
}

int			buttons_main(int call, int x, int y, void **mlx)
{
	// make only one button at time
	button1_main(call, x, y, mlx);
	button2_main(call, x, y, mlx);
	return (0);
}
