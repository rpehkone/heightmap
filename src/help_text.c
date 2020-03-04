/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:59:13 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/04 21:11:21 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	help_text(void **mlx)
{
	static long	color = 0xFFFFFF;
	static int	fade = 0;
	static int	width = 0;
	static int	height = 0;

	if (is_key_down(0, 4))
		fade = 0;
	if (is_key_down(0, 4))
		color = 0xFFFFFF;
	else if (!color)
		return ;
	if (!width)
		width = get_width(NULL);
	if (!height)
		height = get_height(NULL);
	if (fade > 500)
		color -= 0xF0F0F;
	else
		fade++;
	mlx_string_put(mlx[0], mlx[1], width / 2 - (14 / 2 * 9) - 5,
		height - 70, color, "Drag to Rotate");
	mlx_string_put(mlx[0], mlx[1], width / 2 - (14 / 2 * 9) - 5,
		height - 50, color, "Scroll to Zoom");
	mlx_string_put(mlx[0], mlx[1], width / 2 - (21 / 2 * 9) - 5,
		height - 30, color, "Middle-click to Move");
}
