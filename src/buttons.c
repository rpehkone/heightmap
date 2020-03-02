/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/02 23:48:34 by rpehkone         ###   ########.fr       */
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
	if (x > b.x && x < b.x + tmp &&
	y > b.y && y < b.y + tmp2)
	{
		b.b_color = b.bc_color;
		b.t_color = b.tc_color;
		ret = 1;
	}
	if (b.type == 0)
		print_button(&b, mlx);
	return (ret);
}

t_button	set_b_spin(void)
{
	static int	i = 0;
	static int	x = 75;
	t_button	b;

	b.x = x;
	b.y = 0;
	b.size_x = 75;
	b.size_y = 40;
	b.b_color = 0x000000;
	b.bc_color = 0xFFFFFF;
	b.t_color = 0xFFFFFF;
	b.tc_color = 0x000000;
	b.type = 0;
	b.edge = 1;
	b.edge_color = 0xFFFFFF;
	b.stay_down = 1;
	b.is_down = 0;
	ft_strcpy(b.text, "asd");
	if (i == 1)
		ft_strcpy(b.text, "projection");
	if (i == 3)
		ft_strcpy(b.text, "spin");
	x += 75;
	i++;
	return (b);
}

int			buttons_loop(int call, int x, int y, void **mlx)
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
		all_b = (t_button*)malloc(sizeof(t_button) * 10);
		while (i < 10)
		{
			all_b[i] = set_b_spin();
			i++;
		}
	}
	oldx = call == 6 ? x : oldx;
	oldy = call == 6 ? y : oldy;

	i = 1;
	while (i < 10)
	{
		if (handle_button(mlx, all_b[i], oldx, oldy))
		{
			if (call == 4 && x == 1)
			{
				all_b[i].is_down = all_b[i].is_down ? 0 : 1;
				settings[i] = settings[i] ? 0 : 1;
			}
		}
		i++;
	}
	//laita settings[0] ei saa liikuttaa
	//tai return settings[0]
	return (1);
}
