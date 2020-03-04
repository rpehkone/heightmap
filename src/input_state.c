/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 22:35:09 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/04 22:36:04 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_xyz	get_cursor(int x, int y, void **mlx)
{
	static t_xyz	c = {.x = 0, .y = 0, .z = 0};

	if (mlx)
	{
		c.x = x;
		c.y = y;
	}
	return (c);
}

int		is_key_down(int call, int key)
{
	static int	*keyb = NULL;
	int			i;

	if (!keyb)
	{
		i = 0;
		if (!(keyb = (int*)malloc(sizeof(int) * 1000)))
			ft_error(NULL);
		while (i < 1000)
		{
			keyb[i] = 0;
			i++;
		}
	}
	if (call == 0)
		return (keyb[key]);
	else if (call == 1)
		keyb[key] = 1;
	else if (call == 2)
		keyb[key] = 0;
	return (0);
}

int		is_mouse_down(int call, int button)
{
	static int	*mouse = NULL;
	int			i;

	if (!mouse)
	{
		i = 0;
		if (!(mouse = (int*)malloc(sizeof(int) * 1000)))
			ft_error(NULL);
		while (i < 6)
		{
			mouse[i] = 0;
			i++;
		}
	}
	if (call == 0)
		return (mouse[button]);
	else if (call == 1)
		mouse[button] = 1;
	else if (call == 2)
		mouse[button] = 0;
	return (0);
}
