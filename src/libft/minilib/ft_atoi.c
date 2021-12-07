/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 11:11:59 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/17 07:23:29 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atoi(const char *str)
{
	int				x;
	int				com;
	long long int	nb;

	if (str == NULL)
		return (0);
	x = 0;
	nb = 0;
	while ((str[x] > 8 && str[x] < 14)
		|| str[x] == 32)
		x++;
	com = x;
	if (str[x] == '+' || str[x] == '-')
		x++;
	while (str[x] > 47 && str[x] < 58)
	{
		nb = nb * 10 + (str[x] - 48);
		x++;
	}
	if (str[com] == '-')
		return (-nb);
	return (nb);
}
