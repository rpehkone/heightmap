/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2019/12/12 00:42:32 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>

typedef struct	coord {
		float	x;
		float	y;
		float	z;
}				xyz;

void	ft_putnbr(int n)
{
	char	str[11];
	int		tmp;
	int		size;

	size = 0;
	if (n == 0)
		write(1, "0", 1);
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n < 0)
		if (n *= -1)
			write(1, "-", 1);
	tmp = n;
	while (tmp > 0 && ++size)
		tmp /= 10;
	str[size] = '\0';
	while (size--)
	{
		str[size] = n % 10 + '0';
		n /= 10;
	}
	size++;
	while (str[size])
		write(1, &str[size++], 1);
}

float	ft_abs(float n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

void	print_line(xyz *start, xyz *stop, void **mlx, unsigned color)
{
	xyz	step;
	xyz	pos;

	pos.x = start->x;
	pos.y = start->y;
	pos.z = 0;
	step.z = ft_abs(stop->x - start->x) > ft_abs(stop->y - start->y) ?
			ft_abs(stop->x - start->x) : ft_abs(stop->y - start->y);
	step.x = (stop->x - start->x) / (float)step.z;
	step.y = (stop->y - start->y) / (float)step.z;
	while (pos.z <= step.z)
	{
		mlx_pixel_put(mlx[0], mlx[1], pos.x, pos.y, color);
		pos.x += step.x;
		pos.y += step.y;
		pos.z++;
	}
}

void	ft_print(void **mlx, int x, int y, xyz *angle)
{
	xyz start = {.x = 200, .y = 200};
	xyz stop = {.x = 200 + angle->z + angle->y, .y = 200 + angle->x};
	int cpy;

	while (y > 0)
	{
		cpy = x;
		while (cpy > 0)
		{
			start.x += angle->z;
			stop.x += angle->z;
			if (cpy > 1)
				print_line(&start, &stop, mlx, 0xFF0000);
			stop.x -= angle->z;
			stop.y += angle->z;

			if (y > 1)
				print_line(&start, &stop, mlx, 0xFF0000);
			stop.x += angle->z;
			stop.y -= angle->z;
			start.y += angle->x;
			stop.y += angle->x;
			start.x += angle->y;
			stop.x += angle->y;
			cpy--;
		}
		start.x += angle->y;
		stop.x += angle->y;
		start.y += angle->z;
		stop.y += angle->z;
		start.y -= angle->x * (x - 1);
		stop.y -= angle->x * (x - 1);
		start.x -= angle->y * x;
		stop.x -= angle->y * x;
		cpy = x;
		while (cpy > 0)
		{
			start.x -= angle->z;
			stop.x -= angle->z;
			cpy--;
		}
		y--;
	}
}

int		deal_key(int key, void **mlx)
{
	static xyz angle = {.x = 0, .y = 0, .z = 50};

	if (key == 53)
		exit(0);
	else if (key == 0)
		angle.y -= 2;
	else if (key == 2)
		angle.y += 2;
	else if (key == 1)
		angle.x += 2;
	else if (key == 13)
		angle.x -= 2;
	else if (key == 126)
		angle.z += 2;
	else if (key == 125)
		angle.z -= 2;
	mlx_clear_window(mlx[0], mlx[1]);
	ft_print(mlx, 2, 2, &angle);
	return (0);
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	**both;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "fdf");
	both = (void**)malloc(sizeof(void*) * 2);
	both[0] = mlx_ptr;
	both[1] = win_ptr;
	mlx_key_hook(win_ptr, deal_key, both);
	mlx_loop(mlx_ptr);
}
