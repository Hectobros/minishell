/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xconv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 20:15:13 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/20 19:37:32 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_xconv(va_list ap, t_reponse *a, char *base)
{
	unsigned int	x;
	int				size;
	int				nbz;

	x = (unsigned int)va_arg(ap, int);
	size = ft_sizenbx(x, (unsigned int)ft_strlen(base));
	nbz = a->precision - size;
	if (nbz < 1)
		nbz = 0;
	if (size > a->taille)
	{
		while (nbz-- > 0)
			ft_putchar('0', a);
		ft_putnbrebase(x, base, a);
	}
	else
	{
		a->base = base;
		ft_displayx(x, a->taille - (size + nbz), a, nbz);
	}
	return (0);
}

int	ft_sizenbx(unsigned long y, unsigned long x)
{
	int	c;

	c = 0;
	while (y > x - 1)
	{
		y = y / x;
		c++;
	}
	c++;
	return (c);
}

void	ft_displayx(unsigned int x, int nbchar, t_reponse *a, int nbz)
{
	if (a->spec == '-')
		ft_tdispx(x, nbchar, nbz, a);
	else if (a->spec == 'N')
		ft_ndispx(x, nbchar, nbz, a);
	else if (a->spec == '0')
		ft_zdisx(x, nbchar, nbz, a);
}

void	ft_zdisx(unsigned int x, int nbchar, int nbz, t_reponse *a)
{
	unsigned int	y;

	if (a->precision < a->taille && a->point == 1)
	{
		a->precision = t((ft_sizenb(x, 16) > a->precision),
				ft_sizenb(x, 16), a->precision);
		y = t(false, a->taille - a->precision - 1,
				a->taille - a->precision);
		nbchar = 0;
		while (y-- > 0)
			ft_putchar(' ', a);
	}
	y = x;
	while (nbchar-- > 0)
		ft_putchar('0', a);
	while (nbz-- > 0)
		ft_putchar('0', a);
	ft_putnbrebase(y, a->base, a);
}

void	ft_tdispx(unsigned int y, int nbchar, int nbz, t_reponse *a)
{
	while (nbz-- > 0)
		ft_putchar('0', a);
	ft_putnbrebase(y, a->base, a);
	while (nbchar-- > 0)
		ft_putchar(' ', a);
}
