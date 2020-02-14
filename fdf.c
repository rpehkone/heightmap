/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/14 15:24:17 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mouse_control(int call, int *x, int *y, t_xyz *angle)
{
	static int	m1_down = 0;
	static int	m3_down = 0;
	static int	old_x;
	static int	old_y;
	t_xyz		offset;

	m1_down = call == 10 ? 0 : m1_down;
	if (call == 6 && m1_down)
		angle->y += ((float)*x - old_x) / 10;
	if (call == 6 && m1_down)
		angle->x += ((float)*y - old_y) / 10;
	if (!(offset.x = 0) && call == 6 && m3_down)
		offset.x += ((float)*x - old_x);
	if (!(offset.y = 0) && call == 6 && m3_down)
		offset.y += ((float)*y - old_y);
	if (call == 6)
		old_x = *x;
	if (call == 6)
		old_y = *y;
	if ((call == 4 || call == 5) && *x == 1)
		m1_down = m1_down ? 0 : 1;
	if ((call == 4 || call == 5) && *x == 3)
		m3_down = m3_down ? 0 : 1;
	*x = offset.x;
	*y = offset.y;
}

void	reset_line(t_xyz *start, t_xyz *stop, t_xyz *offset, t_xyz *angle)
{
	start->x = 0;
	start->y = 0;
	stop->x = angle->z + angle->y;
	stop->y = angle->x;
	start->x += offset->x;
	start->y += offset->y;
	stop->x += offset->x;
	stop->y += offset->y;
}

int		fdf_main(int call, int x, int y, void **mlx)
{
	static t_xyz	angle = {.x = 2, .y = -5, .z = 30};
	static t_xyz	offset = {.x = 200, .y = 200};
	static int		color = 0xFFFFFF;
	t_xyz			start;
	t_xyz			stop;

	mlx[3] = &color;
	if (call == 4 && x == 4)
		angle.z += (float)angle.z / 5;
	if (call == 4 && x == 5)
		angle.z -= (float)angle.z / 5;
	if (angle.z > 70)
		angle.z = 69;
	if (angle.z < 5)
		angle.z = 5;
	mouse_control(call, &x, &y, &angle);
	offset.x += x;
	offset.y += y;
	reset_line(&start, &stop, &offset, &angle);
	mlx_clear_window(mlx[0], mlx[1]);
	mlx_put_image_to_window(mlx[0], mlx[1], mlx[4], 0, 0);
	ft_printer(mlx, &angle, start, stop);
	return (0);
}

int		fdf(int call, int x, int y, void **mlx)
{
	static int	allow_rotate = 1;

	if (allow_rotate)
		fdf_main(10, x, y, mlx);
	else
		fdf_main(call, x, y, mlx);
	allow_rotate = buttons_main(call, x, y, mlx);
	help_text(mlx);
	return (0);
}
