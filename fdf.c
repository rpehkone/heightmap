/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/02/14 11:05:16 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	ft_abs(float n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

void	print_line(t_xyz *start, t_xyz *stop, void **mlx)
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
		image_pixel_put(mlx, pos.x, pos.y, *(int *)mlx[3]);
		pos.x += step.x;
		pos.y += step.y;
		pos.z++;
	}
}

void	mouse_control(int call, int *x, int *y, t_xyz *angle)
{
	static int	m1_down = 0;
	static int	m3_down = 0;
	static int	old_x;
	static int	old_y;
	t_xyz		offset;

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
	//make bounce back function
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
	fdf_main(call, x, y, mlx);
	buttons_main(call, x, y, mlx);
	help_text(mlx);
	return (0);
}
