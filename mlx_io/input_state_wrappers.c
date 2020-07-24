/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_state_wrappers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 20:08:53 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/12 20:08:56 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_io.h"

t_int_xy	get_cursor(void)
{
	return (set_cursor(0, 0, 0));
}

int			is_mouse_down(int button)
{
	return (set_mouse(0, button));
}

int			is_key_down(int key)
{
	return (set_key(0, key));
}

void	string_to_image(int x, int y, int color, char *str)
{
	static void **mlx = NULL;

	if (!mlx)
		mlx = get_mlx(NULL);
	mlx_string_put(mlx[0], mlx[1], x, y, color, str);
}
