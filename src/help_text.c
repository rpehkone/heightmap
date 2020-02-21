/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:59:13 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/21 16:36:48 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	help_text(void **mlx)
{
	static long	color = 0xFFFFFF;
	static int	fade = 0;
	static int	width = 0;
	static int	height = 0;

	if (!color)
		return ;
	if (!width)
		width = get_width(NULL);
	if (!height)
		height = get_height(NULL);
	if (fade > 500)
	{
		color -= 0xF0000;
		color -= 0xF00;
		color -= 0xF;
	}
	else
		fade++;
	mlx_string_put(mlx[0], mlx[1], width / 2 - (12 / 2 * 9) - 5,
		height - 70, color, "Drag to Warp");
	mlx_string_put(mlx[0], mlx[1], width / 2 - (14 / 2 * 9) - 5,
		height - 50, color, "Scroll to Zoom");
	mlx_string_put(mlx[0], mlx[1], width / 2 - (21 / 2 * 9) - 5,
		height - 30, color, "Middle-click to Move");
}
