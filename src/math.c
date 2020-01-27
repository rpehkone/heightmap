/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:49:05 by rpehkone          #+#    #+#             */
/*   Updated: 2020/01/09 19:37:35 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_abs(double x)
{
	if (x > 0)
		return (x);
	return (-1 * x);
}

double ft_sqrt(double n)
{
	double lo = 0;
	double hi = n;
	double mid;

	for (int i = 0; i < 1000; i++)
	{
		mid = (lo + hi) / 2;
		if (mid * mid == n) return mid;
		if (mid * mid > n) hi = mid;
		else lo = mid;
	}
	return (mid);
}

double sinus(float x)
{
    int i = 1;
    double cur = x;
    double acc = 1;
    double fact= 1;
    double pow = x;
    while (ft_abs(acc) > .00000001 &&  i < 100){
        fact *= ((2*i)*(2*i+1));
        pow *= -1 * x*x; 
        acc =  pow / fact;
        cur += acc;
        i++;
    }
    return cur;
}

double cosinus(float x)
{
    double t, s ;
	double prec = .0001;
    int p;
    p = 0;
    s = 1.0;
    t = 1.0;
    while(ft_abs(t/s) > prec)
    {
        p++;
        t = (-t * x * x) / ((2 * p - 1) * (2 * p));
        s += t;
    }
    return s;
}

void	rotateX(float theta, xyz *nodes)
{
    double sinTheta = sinus(theta);
    double cosTheta = cosinus(theta);

	float y;
	float z;
	int n;
    for (n = 0; n < 8; n++)
	{
        y = nodes[n].y;
        z = nodes[n].z;
        nodes[n].y = y * cosTheta - z * sinTheta;
        nodes[n].z = z * cosTheta + y * sinTheta;
    }
}

void	rotateY(float theta, xyz *nodes)
{
    double sinTheta = sinus(theta);
    double cosTheta = cosinus(theta);

	float x;
	float z;
	int n;
	for (n = 0; n < 8; n++)
	{
		x = nodes[n].x;
		z = nodes[n].z;
		nodes[n].x = x * cosTheta + z * sinTheta;
		nodes[n].z = z * cosTheta - x * sinTheta;
	}
}

void	rotateZ(float theta, xyz *nodes)
{
	double sinTheta = sinus(theta);
	double cosTheta = cosinus(theta);

	float x;
	float y;
	int n;
	for (n = 0; n < 8; n++)
	{
		x = nodes[n].x;
		y = nodes[n].y;
		nodes[n].x = x * cosTheta - y * sinTheta;
		nodes[n].y = y * cosTheta + x * sinTheta;
	}
}
