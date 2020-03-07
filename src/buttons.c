/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 17:56:16 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			handle_button(void **mlx, t_button b)
{
	int		res;
	t_xyz	cursor;

	res = 0;
	cursor = get_cursor(0, 0, NULL);
	if (cursor.x > b.x && cursor.x < b.x + b.size_x &&
	cursor.y > b.y && cursor.y < b.y + b.size_y)
	{
		res = 1;
		if (is_mouse_down(0, 1))
		{
			b.b_color = b.bc_color;
			b.t_color = b.tc_color;
		}
	}
	if (b.is_down)
	{
		b.b_color = b.bd_color;
		b.t_color = b.td_color;
		b.edge_color = b.edgec_color;
	}
	if (res)
		b.t_color = b.tc_color;
	print_button(&b, mlx);
	return (res);
}

void		set_button_text(t_button *b)
{
	static int	i = 0;

	if (i == 0)
		ft_strcpy(b->text, "");
	else if (i == 1)
		ft_strcpy(b->text, "projection");
	else if (i == 2)
		ft_strcpy(b->text, "fov");
	else if (i == 3)
		ft_strcpy(b->text, "spin");
	else if (i == 4)
		ft_strcpy(b->text, "color");
	else if (i == 5)
		ft_strcpy(b->text, "cycle colors");
	else if (i == 6)
		ft_strcpy(b->text, "height coloring");
	else if (i == 7)
		ft_strcpy(b->text, "fps");
	else if (i == 8)
		ft_strcpy(b->text, "reset");
	i++;
}

t_button	init_buttons(void)
{
	static int	x = 0;
	t_button	b;

	b.x = x;
	b.y = 0;
	b.size_y = 30;
	b.b_color = 0xaeacad;
	b.bc_color = 0x807e7f;
	b.bd_color = 0x2755b2;
	b.t_color = 0;
	b.tc_color = 0x707070;
	b.td_color = 0xFFFFFF;
	b.edge = 1;
	b.edge_color = 0xFFFFFF;
	b.edgec_color = 0x707070;
	b.stay_down = 1;
	b.is_down = 0;
	set_button_text(&b);
	b.size_x = ft_strlen(b.text) * 12;
	x += b.size_x + 1;
	return (b);
}

void		on_click(t_button *all_b, int i, int *click)
{
	if (all_b[i].is_down == 0 && (i == 2 || i == 4))
	{
		all_b[2].is_down = 0;
		all_b[4].is_down = 0;
	}
	all_b[i].is_down = all_b[i].is_down ? 0 : 1;
	click[i] = 0;
}

void		buttons_loop(void **mlx)
{
	static t_button	*all_b = NULL;
	static int		click[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int				i;

	if ((i = -1) && !all_b)
	{
		if (!(all_b = (t_button*)malloc(sizeof(t_button) * 9)))
			ft_error(NULL);
		while (++i < 9)
			all_b[i] = init_buttons();
		get_settings(0, all_b);
	}
	if (!(i = 0) && !is_mouse_down(0, 1) && !is_mouse_down(0, 3))
		all_b[0].is_down = 1;
	while (++i < 9)
		if (handle_button(mlx, all_b[i]) || (click[i] = 0))
		{
			all_b[0].is_down = 0;
			if ((click[i] == 2 && !is_mouse_down(0, 1)) ||
				(click[i] == 1 && is_mouse_down(0, 1)) ||
				(click[i] == 0 && !is_mouse_down(0, 1)))
				click[i]++;
			else if (click[i] == 3)
				on_click(all_b, i, click);
		}
}
