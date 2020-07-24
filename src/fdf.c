/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 18:37:25 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	matrix_transform(t_xyz *nodes, int amount)
{
	static float	x = 0;
	static float	x2 = 0;
	static float	y = 0;
	static float	y2 = 0;
	t_int_xy	cursor;

	cursor = get_cursor();
	if (get_settings(3, NULL))
		y += 0.01;
	if (is_mouse_down(1) && get_settings(0, NULL) &&
		!get_settings(4, NULL) && !get_settings(2, NULL))
	{
		x -= (cursor.y - y2) * 0.01;
		y -= (cursor.x - x2) * 0.01;
	}
	x2 = cursor.x;
	y2 = cursor.y;
	rotate_x(-1 * x, nodes, amount);
	rotate_y(y, nodes, amount);
}

int		get_settings(int i, t_button *all_b)
{
	static t_button	*st = NULL;

	if (!st && all_b)
	{
		st = all_b;
		return (0);
	}
	if (i < 0)
	{
		st[i * -1].is_down = 0;
	}
	return (st[i].is_down);
}

void	reset(void)
{
	int i;


	i = 1;
	while (i <= 10)
	{
		get_settings(-1 * i, NULL);
		i++;
	}
	get_color(0xFFFFFF);
	move_center(NULL, NULL, 1);
	add_perspective(NULL, NULL, 1);
	draw(NULL, 0, 1);
	slider_button(0, 1);
	center_image(NULL, NULL, 1);
}

void		render_layer(void)
{
	static t_xyz	*nodes = NULL;
	static t_xyz	*nodes2 = NULL;
	static int		amount = 0;
	int		i;

	if (!nodes || get_settings(8, NULL))
	{
		nodes = make_map(NULL, 0);
		amount = get_map_len(0);
		nodes2 = (t_xyz*)malloc(sizeof(t_xyz) * amount);
		//rotate_x(-1, nodes, get_map_len(0));
		//rotate_y(1, nodes, get_map_len(0));
		reset();
	}
	i = 0;
	while (i < amount)
	{
		nodes2[i].x = nodes[i].x;
		nodes2[i].y = nodes[i].y;
		static int h = 100;
		if (get_settings(9, NULL))
			slider(&h);
		nodes2[i].z = nodes[i].z * (h * 0.01);
		i++;
	}
	matrix_transform(nodes2, amount);
	draw(nodes2, amount, 0);
}

void		fdf(void)
{
	if (is_key_down(53))
		exit(0);
	render_layer();
	button_layer();
	update_image();
	text_layer();
	if (!get_settings(2, NULL) && get_settings(4, NULL))
		gradient();
	clear_image();
}
