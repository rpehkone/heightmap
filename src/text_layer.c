/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_layer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 10:59:13 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 18:29:40 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_fps(void **mlx, int fps)
{
	static int		height = 0;
	char			*str;

	str = NULL;
	if (!height)
		height = get_height(NULL);
	str = ft_itoa(fps);
	mlx_string_put(mlx[0], mlx[1], 10,
	height - 30, 0xFFFF00, str);
	free(str);
	str = NULL;
}

void	fps(void **mlx)
{
	struct timeval	time;
	static long		s = 0;
	static int		i = 0;
	static int		fps = 0;

	i++;
	gettimeofday(&time, NULL);
	if (get_settings(7, NULL))
		put_fps(mlx, fps);
	if (s != time.tv_sec)
	{
		s = time.tv_sec;
		fps = i;
		i = 0;
	}
}

void	button_text(void **mlx)
{
	static t_button *b = NULL;

	if (!b)
		b = get_buttons(NULL);
	for (int i = 0; i < 10; i++)
		mlx_string_put(mlx[0], mlx[1], b[i].x + 6,
			b[i].y + 3, b[i].t_color, b[i].text);
}

void	text_layer()
{
	static long	color = 0xFFFFFF;
	static int	fade = 0;
	static int	width = 0;
	static int	height = 0;
	static void	**mlx = NULL;

	if (!mlx)
		mlx = get_mlx(NULL);
	button_text(mlx);
	fps(mlx);
	fade = is_key_down(4) ? 0 : fade;
	if (is_key_down(4))
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
