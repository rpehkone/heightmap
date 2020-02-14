/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_2_cycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/14 11:52:43 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buttons.h"

void		cycle_colors(void **mlx)
{
	static int	i = 0;
	static int	old;
	double		red;
	double		grn;
	double		blu;

	if (*(int*)mlx[3] != old && *(int*)mlx[3] != 0xFFFFFF)
		while (*(int*)mlx[3] != old)
		{
			if (i > 310)
				i = 0;
			red = sin(0.02 * i + 0) * 127 + 128;
			grn = sin(0.02 * i + 2) * 127 + 128;
			blu = sin(0.02 * i + 4) * 127 + 128;
			old = ((int)red * 65536 + (int)grn * 256 + (int)blu);
			i++;
		}
	if (i > 310)
		i = 0;
	red = sin(0.02 * i + 0) * 127 + 128;
	grn = sin(0.02 * i + 2) * 127 + 128;
	blu = sin(0.02 * i + 4) * 127 + 128;
	old = ((int)red * 65536 + (int)grn * 256 + (int)blu);
	*(int*)mlx[3] = old;
	i++;
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

	oldx = call == 6 ? x : oldx;
	oldy = call == 6 ? y : oldy;
	if (!b_cycle)
		b_cycle = set_b_cycle();
	if (handle_button(mlx, *b_cycle, oldx, oldy) && call == 5 && x == 1)
		cycle = cycle ? 0 : 1;
	b_cycle->tc_color = 0;
	edit_button2(b_cycle, cycle, mlx);
	return (cycle);
}
