/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/03/07 18:37:25 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_vertices(float angle, t_xyz *vertices, int amount, int axis_x)
{
	float	sin_angle;
	float	cos_angle;
	float	a;
	float	b;
	int		n;

	n = -1;
	sin_angle = sin(angle);
	cos_angle = cos(angle);
	while (++n < amount)
		if (axis_x)
		{
			a = vertices[n].y;
			b = vertices[n].z;
			vertices[n].y = a * cos_angle - b * sin_angle;
			vertices[n].z = b * cos_angle + a * sin_angle;
		}
		else
		{
			a = vertices[n].x;
			b = vertices[n].z;
			vertices[n].x = a * cos_angle + b * sin_angle;
			vertices[n].z = b * cos_angle - a * sin_angle;
		}
}

void	rotate(t_xyz *vertices, int amount, struct s_settings *settings)
{
	static float	x = 0;
	static float	x2 = 0;
	static float	y = 0;
	static float	y2 = 0;
	t_int_xy	cursor;

	cursor = get_cursor();
	if (settings->spin_b)
		y += 0.01;
	if (!settings->active_layer && is_mouse_down(1))
	{
		x -= (cursor.y - y2) * 0.01;
		y -= (cursor.x - x2) * 0.01;
	}
	x2 = cursor.x;
	y2 = cursor.y;
	rotate_vertices(-1 * x, vertices, amount, 1);
	rotate_vertices(y, vertices, amount, 0);
}

void		render_layer(struct s_settings *settings)
{
	static t_xyz	*vertices_save = NULL;
	static t_xyz	*vertices = NULL;
	static int		amount = 0;
	int		i;

	if (!vertices_save)
	{
		vertices_save = make_map(NULL, NULL, NULL);
		amount = get_map_len(0);
		vertices = (t_xyz*)malloc(sizeof(t_xyz) * amount);
	}
	i = 0;
	while (i < amount)
	{
		vertices[i].x = vertices_save[i].x;
		vertices[i].y = vertices_save[i].y;
		vertices[i].z = vertices_save[i].z * settings->height;
		i++;
	}
	rotate(vertices, amount, settings);
	i = -1;
	while (i++ < amount)
		vertices[i].z += ((settings->fov + 2) * 500);
	draw(vertices, amount, settings);
}

void		fdf(void)
{
	static struct s_settings	settings;
	static int			first = 1;

	if (is_key_down(53))
		exit(0);
	else if (first)
	{
		ft_bzero(&settings, sizeof(settings));
		settings.fov = 1;
		settings.color.x = 0xFFFFFF;
		settings.color.y = 0xFFFFFF;
		settings.height = 1;
		first = 0;
	}
	update_image();
	render_layer(&settings);
	button_layer(&settings);
	text_layer(&settings);
}
