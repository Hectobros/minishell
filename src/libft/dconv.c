/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dconv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:25:23 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/20 19:36:44 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_dconv(va_list ap, t_reponse *a, char *base)
{
	int				x;
	int				size;
	int				nbz;
	unsigned int	y;

	x = va_arg(ap, int);
	size = ft_sizenb(x, (int)ft_strlen(base));
	nbz = a->precision - size;
	nbz = t((nbz < 1), 0, nbz);
	if (size > a->taille)
	{
		if (x < 0)
			ft_putchar('-', a);
		y = t(x < 0, x * -1, x);
		while (nbz-- > 0)
			ft_putchar('0', a);
		ft_putnbrebase(y, base, a);
	}
	else
	{
		a->base = base;
		ft_displayd(x, a->taille - (size + nbz), a, nbz);
	}
	return (0);
}

int	ft_sizenb(int x, int tbase)
{
	unsigned int	y;
	int				c;

	c = 0;
	if (x < 0)
		y = x * -1;
	else
		y = x;
	while (y > (unsigned int)tbase - 1)
	{
		y = y / tbase;
		c++;
	}
	c++;
	return (c);
}

void	ft_displayd(int x, int nbchar, t_reponse *a, int nbz)
{
	if (a->spec == '-')
		ft_tdisp(x, nbchar, nbz, a);
	else if (a->spec == 'N')
		ft_ndisp(x, nbchar, nbz, a);
	else if (a->spec == '0')
		ft_zdisp(x, nbchar, nbz, a);
}

void	ft_zdisp(int x, int nbchar, int nbz, t_reponse *a)
{
	int	y;

	if (a->precision < a->taille && a->point == 1 && a->precision > 0)
	{
		a->precision = t(ft_sizenb(x, (int)ft_strlen(a->base)) > a->precision,
				ft_sizenb(x, (int)ft_strlen(a->base)), a->precision);
		y = t(x < 0, a->taille - a->precision - 1, a->taille - a->precision);
		nbchar = 0;
		while (y-- > 0)
			ft_putchar(' ', a);
	}
	if (x < 0)
	{
		ft_putchar('-', a);
		y = x * -1;
		nbchar--;
	}
	else
		y = x;
	while (nbchar-- > 0)
		ft_putchar('0', a);
	while (nbz-- > 0)
		ft_putchar('0', a);
	ft_putnbrebase(y, a->base, a);
}

void	ft_tdisp(int x, int nbchar, int nbz, t_reponse *a)
{
	int	y;

	if (x < 0)
	{
		nbchar--;
		ft_putchar('-', a);
		y = x * -1;
	}
	else
		y = x;
	while (nbz-- > 0)
		ft_putchar('0', a);
	ft_putnbrebase(y, a->base, a);
	while (nbchar-- > 0)
		ft_putchar(' ', a);
}
