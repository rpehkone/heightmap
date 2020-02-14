/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:59:13 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/14 11:34:06 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	help_text(void **mlx)
{
	static int	fade = 0;
	static long	color = 0xFFFFFF;

	if (!color)
		return ;
	if (fade > 300)
	{
		color -= 0xF0000;
		color -= 0xF00;
		color -= 0xF;
	}
	else
		fade++;
	mlx_string_put(mlx[0], mlx[1],
		*(int*)mlx[5] / 2 - (12 / 2 * 9) - 5,
		*(int*)mlx[6] - 70, color, "Drag to Warp");
	mlx_string_put(mlx[0], mlx[1],
		*(int*)mlx[5] / 2 - (14 / 2 * 9) - 5,
		*(int*)mlx[6] - 50, color, "Scroll to Zoom");
	mlx_string_put(mlx[0], mlx[1],
		*(int*)mlx[5] / 2 - (21 / 2 * 9) - 5,
		*(int*)mlx[6] - 30, color, "Middle-click to Move");
}
