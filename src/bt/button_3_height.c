/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_3_height.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/19 20:26:53 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_button	*set_b_middle(void)
{
	static t_button	b = {.text = ""};

	b.x = 352;
	b.y = 15;
	b.size_x = 3;
	b.size_y = 11;
	b.b_color = 0xFFFFFF;
	b.bc_color = 0xFFFFFF;
	b.t_color = 0;
	b.tc_color = 0;
	b.type = 0;
	return (&b);
}

void		draw_middle(int call, int x, int y, void **mlx)
{
	static t_button	*middle = NULL;
	static int		oldy = 0;
	static int		oldx = 0;

	oldx = call == 6 ? x : oldx;
	oldy = call == 6 ? y : oldy;
	if (!middle)
		middle = set_b_middle();
	handle_button(mlx, *middle, oldx, oldy);
}

t_button	*set_b_height(void)
{
	static t_button	b = {.text = "Height"};

	b.x = 150;
	b.y = 0;
	b.size_x = 90;
	b.size_y = 40;
	b.b_color = 0x000000;
	b.bc_color = 0xFFFFFF;
	b.t_color = 0xFFFFFF;
	b.tc_color = 0x000000;
	b.type = 0;
	return (&b);
}

void		edit_button3(t_button *b, int i, int call, int x)
{
	static int	m1_down = 0;

	if (i)
	{
		b->b_color = 0xFFFFFF;
		b->bc_color = 0xFFFFFF;
		b->t_color = 0;
		b->tc_color = 0;
	}
	else
	{
		b->b_color = 0;
		b->bc_color = 0xFFFFFF;
		b->t_color = 0xFFFFFF;
		b->tc_color = 0;
	}
	if (call == 4 && x == 1)
		m1_down = 1;
	if (call == 5 && x == 1)
		m1_down = 0;
	if (m1_down && call == 22)
		b->tc_color = 0xFFFFFF;
	else
		b->tc_color = 0;
}

int			button3_main(int call, int x, int y, void **mlx)
{
	static t_button	*b_height = NULL;
	static int		oldy = 0;
	static int		oldx = 0;
	static int		draw = 0;
	int				ret;

	oldx = call == 6 ? x : oldx;
	oldy = call == 6 ? y : oldy;
	if (!b_height)
		b_height = set_b_height();
	if ((ret = handle_button(mlx, *b_height, oldx, oldy)) &&
	call == 5 && x == 1)
		draw = draw ? 0 : 1;
	if (draw)
		ret += draw_slider(call, x, y, mlx);
	if (draw)
		draw_middle(call, x, y, mlx);
	if (ret && call != 4 && call != 5)
		edit_button3(b_height, draw, 22, x);
	else
		edit_button3(b_height, draw, call, x);
	return (ret);
}
