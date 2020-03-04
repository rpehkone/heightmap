/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/05 01:21:51 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		print_button2(t_xyz *start, t_xyz *stop, int color, void **mlx)
{
	t_xyz	step;
	t_xyz	pos;

	pos.x = start->x;
	pos.y = start->y;
	pos.z = 0;
	step.z = ft_abs(stop->x - start->x) > ft_abs(stop->y - start->y) ?
			ft_abs(stop->x - start->x) : ft_abs(stop->y - start->y);
	step.x = (stop->x - start->x) / (float)step.z;
	step.y = (stop->y - start->y) / (float)step.z;
	while (pos.z <= step.z)
	{
		image_pixel_put(mlx, pos.x, pos.y, color);
		pos.x += step.x;
		pos.y += step.y;
		pos.z++;
	}
}

void		print_edge(t_xyz start, t_xyz stop, t_button *b, void **mlx)
{
	start.x = b->x;
	start.y = b->y;
	stop.x = b->x + b->size_x;
	stop.y = b->y;
	print_button2(&start, &stop, b->edge_color, mlx);
	stop.x = b->x;
	stop.y = b->y + b->size_y;
	print_button2(&start, &stop, b->edge_color, mlx);
	start.x = b->x;
	start.y = b->y + b->size_y;
	stop.x = b->x + b->size_x;
	stop.y = b->y + b->size_y;
	print_button2(&start, &stop, b->edge_color, mlx);
	start.x = b->x + b->size_x;
	start.y = b->y;
	stop.x = b->x + b->size_x;
	stop.y = b->y + b->size_y;
	print_button2(&start, &stop, b->edge_color, mlx);
}

void		print_button(t_button *b, void **mlx)
{
	t_xyz start;
	t_xyz stop;

	start.x = b->x;
	start.y = b->y;
	stop.x = b->x + b->size_x;
	stop.y = b->y;
	while (start.y < b->y + b->size_y)
	{
		print_button2(&start, &stop, b->b_color, mlx);
		start.y++;
		stop.y++;
	}
	//if (i == 1 || i == 4 || i == 5)
	//	;//b.size_x -= 5;
	mlx_string_put(mlx[0], mlx[1], b->x + 6,
			b->y + 3, b->t_color, b->text);
	if (b->edge)
		print_edge(start, stop, b, mlx);
}

int			*get_settings(void)
{
	static int	*st = NULL;
	int			i;

	if (!st)
	{
		i = 0;
		st = (int*)malloc(sizeof(int) * 10);
		while (i < 10)
		{
			st[i] = 0;
			i++;
		}
		st[0] = 1;
	}
	return (st);
}

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
		b.b_color = b.bc_color;
		b.t_color = b.tc_color;
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
	if (i == 1)
		ft_strcpy(b->text, "projection");
	if (i == 2)
		ft_strcpy(b->text, "depth");
	if (i == 3)
		ft_strcpy(b->text, "spin");
	if (i == 4)
		ft_strcpy(b->text, "focal lenght");
	if (i == 5)
		ft_strcpy(b->text, "color");
	if (i == 6)
		ft_strcpy(b->text, "cycle colors");
	if (i == 7)
		ft_strcpy(b->text, "height coloring");
	if (i == 8)
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
	b.b_color = 0xFFFFFF;
	b.bc_color = 0;
	b.bd_color = 0x000000;
	b.t_color = 0;
	b.tc_color = 0x707070;
	b.td_color = 0xFFFFFF;
	b.edge = 1;
	b.edge_color = 0xFFFFFF;
	b.edgec_color = 0x707070;
	b.stay_down = 1;
	b.is_down = 0;
	set_button_text(&b);
	//b.size_x = ft_strlen(b.text) * 11.5;
	b.size_x = ft_strlen(b.text) * 12;
	x += b.size_x + 1;
	return (b);
}

void		on_click(int *settings, t_button *all_b, int i, int *click)
{
	if (i == 8)
		exit(0);
	else if (all_b[i].is_down == 0 && (i == 2 || i == 4 | i == 5))
	{
		settings[2] = 0;
		settings[4] = 0;
		settings[5] = 0;
		all_b[2].is_down = 0;
		all_b[4].is_down = 0;
		all_b[5].is_down = 0;
	}
	all_b[i].is_down = all_b[i].is_down ? 0 : 1;
	settings[i] = settings[i] ? 0 : 1;
	settings[0] = 0;
	click[i] = 0;
}

int			buttons_loop(void **mlx)
{
	static t_button	*all_b = NULL;
	static int		*settings = NULL;
	static int		click[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	int				i;

	if (!all_b)
		all_b = (t_button*)malloc(sizeof(t_button) * 9);
	if ((i = -1) && !settings)
		while (++i < 9)
			all_b[i] = init_buttons();
	if (!settings)
		settings = get_settings();
	if (!(i = 0) && !is_mouse_down(0, 1) && !is_mouse_down(0, 3))
		settings[0] = 1;
	while (++i < 9)
		if (handle_button(mlx, all_b[i]) || (click[i] = 0))
		{
			if ((!(settings[0] = 0) && click[i] == 2 && !is_mouse_down(0, 1)) ||
				(click[i] == 1 && is_mouse_down(0, 1)) ||
				(click[i] == 0 && !is_mouse_down(0, 1)))
				click[i]++;
			else if (click[i] == 3)
				on_click(settings, all_b, i, click);
		}
	return (settings[0]);
}
