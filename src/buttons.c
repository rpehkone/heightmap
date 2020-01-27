/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/12 18:25:06 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
//remove button ->
void	putsquare(button *b, void **mlx)
{
	xyz start;
	xyz stop;

	start.x = b->x;
	start.y = b->y;
	stop.x = b->x + b->size_x;
	stop.y = b->y;
	while (start.y < b->y + b->size_y)
	{
		print_line(&start, &stop, mlx, b->b_color);
		start.y++;
		stop.y++;
	}
	mlx_string_put(mlx[0], mlx[1],
			b->x + b->size_x / 2 - (ft_strlen(b->text) / 2 * 9),
			b->y + b->size_y / 2 - 11, b->t_color, b->text);
}

int		handle_button(void **mlx, button b, int x, int y)
{
	int ret;
	coords position = {.x = b.y, .y = b.x, .z = b.size_x};

	ret = 0;
	int tmp = b.size_x;
	int tmp2 = b.size_y;
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
		putsquare(&b, mlx);
	else//					fill
		putcircle(&position, 1, b.b_color, mlx);
	return (ret);
}
