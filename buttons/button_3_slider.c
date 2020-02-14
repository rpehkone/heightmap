/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_3_height.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/14 13:21:00 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buttons.h"

t_button	*set_slider_back(void)
{
	static t_button	b = {.text = ""};

	b.x = 250;
	b.y = 18;
	b.size_x = 202;
	b.size_y = 4;
	b.b_color = 0xFFFFFF;
	b.bc_color = 0xFFFFFF;
	b.t_color = 0xFFFFFF;
	b.tc_color = 0x000000;
	b.type = 0;
	return (&b);
}

t_button	*set_slider(void)
{
	static t_button	b = {.text = ""};

	b.x = 358;
	b.y = 11;
	b.size_x = 6;
	b.size_y = 20;
	b.b_color = 0xFFFFFF;
	b.bc_color = 0xFFFFFF;
	b.t_color = 0xFFFFFF;
	b.tc_color = 0x000000;
	b.type = 0;
	return (&b);
}

void		draw_slider(int call, int x, int y, void **mlx)
{
	static t_button	*slider_back = NULL;
	static t_button	*slider = NULL;
	static int		oldy = 0;
	static int		oldx = 0;
	static int		move = 0;

	oldx = call == 6 ? x : oldx;
	oldy = call == 6 ? y : oldy;
	if (call == 5 && x == 1)
		move = 0;
	if (!slider_back)
		slider_back = set_slider_back();
	if (!slider)
		slider = set_slider();
	handle_button(mlx, *slider_back, oldx, oldy);
	slider->x = move ? oldx : slider->x;
	if (slider->x < 250)
		slider->x = 250;
	if (slider->x > 450 - 4)
		slider->x = 450 - 4;
	if (slider->x < 353 && slider->x > 347)
		slider->x = 350;
	*(float*)mlx[7] = move ? ((float)slider->x - 350) / 100 : *(float*)mlx[7];
	if (handle_button(mlx, *slider, oldx, oldy) && call == 4 && x == 1)
		move = 1;
}
