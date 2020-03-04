/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/04 21:14:16 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_button2(t_xyz *start, t_xyz *stop, int color, void **mlx)
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

void	print_button(t_button *b, void **mlx)
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
	mlx_string_put(mlx[0], mlx[1],
			b->x + b->size_x / 2 - (ft_strlen(b->text) / 2 * 9) - 5,
			b->y + b->size_y / 2 - 12, b->t_color, b->text);
	if (b->edge)
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
}

int		*get_settings(void)
{
	static int *st = NULL;
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

int		handle_button(void **mlx, t_button b, int x, int y)
{
	int ret;
	int tmp;
	int tmp2;

	tmp = b.size_x;
	tmp2 = b.size_y;
	ret = 0;
	if (b.type == 1)
	{
		tmp *= 2;
		tmp2 *= 2;
	}
	if (b.is_down)
	{
		b.b_color = b.bc_color;
		b.t_color = b.tc_color;
	}
	if (x > b.x && x < b.x + tmp &&
	y > b.y && y < b.y + tmp2)
	{
		b.b_color = b.bc_color;
		b.t_color = b.tc_color;
		ret = 1;
		if (b.is_down)
			b.t_color = 0x707070;
	}
	if (b.type == 0)
		print_button(&b, mlx);
	return (ret);
}

t_button	set_b_spin(void)
{
	static int	i = 0;
	static int	x = 0;
	t_button	b;

	b.x = x;
	b.y = 0;
	b.size_y = 30;
	b.b_color = 0x000000;
	b.bc_color = 0xFFFFFF;
	b.t_color = 0xFFFFFF;
	b.tc_color = 0x000000;
	b.type = 0;
	b.edge = 1;
	b.edge_color = 0xFFFFFF;
	b.stay_down = 1;
	b.is_down = 0;
	if (i == 1)
		ft_strcpy(b.text, "projection");
	if (i == 2)
		ft_strcpy(b.text, "depth");
	if (i == 3)
		ft_strcpy(b.text, "spin");
	if (i == 4)
		ft_strcpy(b.text, "focal lenght");
	if (i == 5)
		ft_strcpy(b.text, "color");
	if (i == 6)
		ft_strcpy(b.text, "cycle colors");
	if (i == 7)
		ft_strcpy(b.text, "height coloring");
	if (i == 8)
		ft_strcpy(b.text, "reset");
	b.size_x = ft_strlen(b.text) * 12;
	x += ft_strlen(b.text) * 12;
	i++;
	return (b);
}

int			buttons_loop(void **mlx)
{
	static int		oldy = 0;
	static int		oldx = 0;
	static t_button	*all_b = NULL;
	static int		*settings = NULL;
	int				i;;

	i = 0;
	if (!settings)
		settings = get_settings();
	if (!all_b)
	{
		all_b = (t_button*)malloc(sizeof(t_button) * 9);
		while (i < 9)
		{
			all_b[i] = set_b_spin();
			i++;
		}
	}
	i = 1;
	while (i < 9)
	{
		if (handle_button(mlx, all_b[i], oldx, oldy))
		{
			if (is_mouse_down(0, 1))
			{
				if (i == 8)
					exit(0);
				if (all_b[i].is_down == 0 && (i == 2 || i == 4 | i == 5))
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
			}
		}
		if (!is_mouse_down(0, 1))
			settings[0] = 1;
		i++;
	}
	//laita settings[0] ei saa liikuttaa
	//tai return settings[0]
	return (settings[0]);
}
