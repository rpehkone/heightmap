/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2019/12/11 21:46:01 by rpehkone         ###   ########.fr       */
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

void	swap(int *x, int *y)
{
	int tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
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

void	ft_print(void **mlx, xyz start, xyz stop)
{
	print_line(&start, &stop, mlx, 0xFF0000);
}

int		deal_key(int key, void **mlx)
{
	static xyz stop = {.x = 500, .y = 500};
	static xyz start = {.x = 250, .y = 250};

	if (key == 53)
		exit(0);
	else if (key == 0)
		start.x -= 50;
	else if (key == 2)
		start.x += 50;
	else if (key == 1)
		start.y += 50;
	else if (key == 13)
		start.y -= 50;
	else if (key == 123)
		stop.x -= 50;
	else if (key == 124)
		stop.x += 50;
	else if (key == 125)
		stop.y += 50;
	else if (key == 126)
		stop.y -= 50;
	ft_print(mlx, start, stop);
	ft_putnbr(key);
	write(1, ", ", 2);
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
