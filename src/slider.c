/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:28:22 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 18:27:03 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_slider_button(int x)
{
	t_xyz	start;
	t_xyz	stop;
	t_xyz	color;
	int		i;

	color.x = 0xFFFFFF;
	color.y = 0xFFFFFF;
	color.z = 1;
	start.x = x;
	start.y = 38;
	stop.x = x;
	stop.y = 49;
	print_line(start, stop, color);
	i = 0;
	while (i < 5)
	{
		start.x++;
		stop.x++;
		print_line(start, stop, color);
		i++;
	}
}

void	slider_button(float *n)
{
	int	slider_x;
	static int	allow_move = 0;
	t_int_xy	cursor;

	slider_x = (((float)(*n + 2) / (float)4) * 200) + 5;
	cursor = get_cursor();
	if (cursor.x < 5)
		cursor.x = 5;
	if (cursor.x > 205)
		cursor.x = 205;
	if (cursor.x < 110 && cursor.x > 100)
		cursor.x = 105;
	if (cursor.x < slider_x + 10 && cursor.x > slider_x - 5 &&
		cursor.y > 30 && cursor.y < 55)
		allow_move = 1;
	if (!is_mouse_down(1))
		allow_move = 0;
	//printf("1 %d\n", allow_move);
	//printf("c %d\n", cursor.x);
	if (allow_move)
		slider_x = cursor.x;
	//printf("3 %d\n", slider_x);
	print_slider_button(slider_x);
	*n = ((((float)(slider_x - 5) / (float)200) * (float)4)) - 2;
	printf("2 %f\n", *n);
	//exit(0);
}

void	print_mid()
{
	t_xyz	start;
	t_xyz	stop;
	t_xyz	color;
	int		i;

	color.x = 0x707070;
	color.y = 0x707070;
	color.z = 1;
	start.x = 106;
	start.y = 40;
	stop.x = 106;
	stop.y = 47;
	i = 0;
	while (i < 3)
	{
		start.x++;
		stop.x++;
		print_line(start, stop, color);
		i++;
	}
}

void	check_collision(void)
{
	t_int_xy	cursor;

	if (is_mouse_down(1))
	{
		cursor = get_cursor();
		if (cursor.x < 220 && (cursor.y < 60 && cursor.y > 30))
			return ;
		else if (cursor.y > 30)
		{
			get_settings(- B_FOV, NULL);
			get_settings(- B_HEIGHT, NULL);
		}
	}
}

void	slider(float *n)
{
	t_xyz	start;
	t_xyz	stop;
	t_xyz	color;
	int		i;

	print_mid();
	color.x = 0x707070;
	color.y = 0x707070;
	color.z = 1;
	start.x = 5;
	start.y = 41;
	stop.x = 210;
	stop.y = 41;
	i = 0;
	while (i < 4)
	{
		start.y++;
		stop.y++;
		print_line(start, stop, color);
		i++;
	}
	check_collision();
	slider_button(n);
}
