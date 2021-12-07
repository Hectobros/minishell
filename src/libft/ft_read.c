/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 10:43:49 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/20 19:00:23 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_reponse	*ft_reader(va_list ap, char *test, t_reponse *a)
{
	ft_conv(test, a);
	ft_spec(ap, test, a);
	ft_taille(ap, test, a);
	if (a->point == 1)
		a = ft_precision(ap, test, a);
	return (a);
}

t_reponse	*ft_spec(va_list ap, char *test, t_reponse *a)
{
	int	z;

	if (test[a->x] == '0' || test[a->x] == '-')
		ft_specspe(test, a);
	else if (test[a->x] == '*')
	{
		z = va_arg(ap, int);
		if (z < 0)
		{
			a->spec = '-';
			a->taille = z * -1;
		}
		else
		{
			a->spec = 'N';
			a->taille = z;
		}
		a->x = a->x + 1;
	}
	else
		a->spec = 'N';
	return (a);
}

t_reponse	*ft_taille(va_list ap, char *test, t_reponse *a)
{
	if (a->taille == -1)
	{
		if (test[a->x] == '*')
		{
			a->taille = va_arg(ap, int);
			if (a->taille < 0)
			{
				a->taille = a->taille * -1;
				a->spec = '-';
			}
		}
		else
		{
			a->taille = ft_atoi(test + a->x);
			if (a->taille < 0)
			{
				a->taille = a->taille * -1;
				a->spec = '-';
			}
		}
	}
	return (a);
}

t_reponse	*ft_conv(char *test, t_reponse *a)
{
	int	x;

	x = a->x;
	while (test[x] != 'c' && test[x] != 's' && test[x] != 'p'
		&& test[x] != 'd' && test[x] != 'i'
		&& test[x] != 'u' && test[x] != 'x' && test[x] != '%'
		&& test[x] != 'X')
	{
		if (test[x] == '.')
			a->point = 1;
		x++;
	}
	a->convertion = test[x];
	a->y = x;
	return (NULL);
}

t_reponse	*ft_precision(va_list ap, char *test, t_reponse *a)
{
	int	x;

	x = a->x;
	while (test[x] != '.')
		x++;
	x++;
	if (test[x] == '*')
		a->precision = va_arg(ap, int);
	else
		a->precision = ft_atoi(test + x);
	if (a->precision < 0)
	{
		a->precision = -1;
		a->point = -1;
	}
	if (a->spec == '0' && a->precision < a->taille && a->precision >= 0)
		a->spec = 'N';
	return (a);
}
