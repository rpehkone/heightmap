/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ispunct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpehkone <rpehkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:25:19 by rpehkone          #+#    #+#             */
/*   Updated: 2019/10/31 16:32:59 by rpehkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_ispunct(int c)
{
	if ((c >= '!' && c <= '/') || (c >= ':' && c <= '@'))
		return (1);
	return ((c >= '[' && c <= 96) || (c >= '{' && c <= '~'));
}
