/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_layer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 18:48:58 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
-       b.b_color = 0xaeacad;
-       b.bc_color = 0x807e7f;
-       b.bd_color = 0x2755b2;
-       b.t_color = 0;
-       b.tc_color = 0x707070;
-       b.td_color = 0xFFFFFF;
-       b.edge = 1;
-       b.edge_color = 0xFFFFFF;
-       b.edgec_color = 0x707070;
*/
int			handle_button(t_button b)
{
	int		res;
	t_int_xy	cursor;
	struct s_xyz start = {.x = b.x, .y = 0};
	struct s_xyz stop = {.x = b.x + b.size_x, .y = 0};
	struct s_xyz color = {.x = 0xaeacad, .y = 0};
	struct s_xyz edge = {.x = 0x555555, .y = 0x555555};
	int text_color = 0;

	res = 0;
	cursor = get_cursor();
	if (b.is_on)
	{
		color.x = 0x2755b2;
		text_color = 0xFFFFFF;
	}
	if (cursor.x > b.x && cursor.x < b.x + b.size_x &&
	cursor.y > 0 && cursor.y < 30)
	{
		res++;
		color.x = 0x807e7f;
		text_color = 0x707070;
		if (is_mouse_down(1))
		{
			color.x = 0x2755b2;
			res++;
		}
	}
	color.y = color.x;
	for (int i = 0; i < 30; i++)
	{
		if (!i || i == 29)
			print_line(start, stop, edge);
		else
			print_line(start, stop, color);
		start.y++;
		stop.y++;
	}
	string_to_image(b.x + 2, 4, text_color, b.text);
	return (res);
}

void		set_button_text(t_button *b, int i)
{
	b->text = (char*)malloc(sizeof(char) * 20);
	if (i == 0)
		ft_strcpy(b->text, "projection");
	else if (i == 1)
		ft_strcpy(b->text, "fov");
	else if (i == 2)
		ft_strcpy(b->text, "spin");
	else if (i == 3)
		ft_strcpy(b->text, "color");
	else if (i == 4)
		ft_strcpy(b->text, "cycle colors");
	else if (i == 5)
		ft_strcpy(b->text, "height");
	else if (i == 6)
		ft_strcpy(b->text, "height coloring");
	else if (i == 7)
		ft_strcpy(b->text, "fps");
	else if (i == 8)
		ft_strcpy(b->text, "reset");
}

t_button	*init_buttons(void)
{
	t_button *all_b;
	int	x;
	int	i;

	if (!(all_b = (t_button*)malloc(sizeof(t_button) * 9)))
		ft_error();
	x = 0;
	i = 0;
	while (i < 9)
	{
		all_b[i].x = x;
		all_b[i].is_on = 0;
		set_button_text(&all_b[i], i);
		all_b[i].size_x = ft_strlen(all_b[i].text) * 12;
		x += all_b[i].size_x + 1;
		i++;
	}
	return (all_b);
}

void		disable_others(struct s_settings *s, struct s_button *b, int i)
{
	if (!b[i].is_on && (i == 1 || i == 3 || i == 5))
	{
		s->fov_b = 0;
		s->color_b = 0;
		s->height_b = 0;
		b[1].is_on = 0;
		b[3].is_on = 0;
		b[5].is_on = 0;
	}
}

void		reset(struct s_settings *s, struct s_button *b)
{
	int	i;

	if (s->reset_b)
	{
		s->projection_b = 0;
		s->fov_b = 0;
		s->fov = 1;
		s->spin_b = 0;
		s->color_b = 0;
		s->cycle_b = 0;
		s->height_b = 0;
		s->height = 1;
		s->height_color_b = 0;
		s->fps_b = 0;
	//	s->reset_b = 0;
		s->color.x = 0xFFFFFF;
		s->color.y = 0xFFFFFF;
		i = -1;
		while (++i < 9)
			b[i].is_on = 0;
	}
}

void		on_click(struct s_settings *s, int i, int *click)
{

	if (i == 0)
		s->projection_b = s->projection_b ? 0 : 1;
	else if (i == 1)
		s->fov_b = s->fov_b ? 0 : 1;
	else if (i == 2)
		s->spin_b = s->spin_b ? 0 : 1;
	else if (i == 3)
		s->color_b = s->color_b ? 0 : 1;
	else if (i == 4)
		s->cycle_b = s->cycle_b ? 0 : 1;
	else if (i == 5)
		s->height_b = s->height_b ? 0 : 1;
	else if (i == 6)
		s->height_color_b = s->height_color_b ? 0 : 1;
	else if (i == 7)
		s->fps_b = s->fps_b ? 0 : 1;
	else if (i == 8)
		s->reset_b = s->reset_b ? 0 : 1;
	click[i] = 0;
}

void		modify_settings(struct s_settings *settings)
{
	t_int_xy cursor;

	cursor = get_cursor();
	settings->active_layer = 0;
	if (cursor.x < 769 && cursor.y < 30)
		settings->active_layer = 1;
	if (settings->height_b)
	{
		slider(&settings->height);
		if (cursor.x < 250 && cursor.y < 60)
			settings->active_layer = 1;
	}
	else if (settings->fov_b)
	{
		slider(&settings->fov);
		if (cursor.x < 250 && cursor.y < 60)
			settings->active_layer = 1;
	}
	else if (settings->color_b)
	{
		gradient(settings);
		if (cursor.x < 310 && cursor.y < 340)
			settings->active_layer = 1;
	}
	if (settings->cycle_b)
		cycle_colors(&settings->color);
}

void		button_layer(struct s_settings *settings)
{
	static t_button	*all_b = NULL;
	static int		click[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	int			i;

	if (!all_b)
		all_b = init_buttons();
	i = 0;
	while (i < 9)
	{
		if (handle_button(all_b[i]) || (click[i] = 0))
		{
			if ((click[i] == 2 && !is_mouse_down(1)) ||
				(click[i] == 1 && is_mouse_down(1)) ||
				(click[i] == 0 && !is_mouse_down(1)))
				click[i]++;
			else if (click[i] == 3)
			{
				disable_others(settings, all_b, i);
				on_click(settings, i, click);
				all_b[i].is_on = all_b[i].is_on ? 0 : 1;
				reset(settings, all_b);
			}
		}
		i++;
	}
	modify_settings(settings);
}
