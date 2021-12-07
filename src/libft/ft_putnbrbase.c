/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:29:12 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/20 18:54:46 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbrebase(unsigned long x, char *base, t_reponse *a)
{
	unsigned long	tbase;
	unsigned long	nb;

	if (x == 0 && a->precision == 0 && a->taille == 0)
		a->taille = 0;
	else if (x == 0 && a->precision == 0)
		ft_putchar(' ', a);
	else if (!(x == 0 && a->precision == 0))
	{
		tbase = (unsigned int)ft_strlen(base);
		nb = x;
		if (nb > tbase - 1)
		{
			ft_putnbrebase(nb / tbase, base, a);
			ft_putchar(base[nb % tbase], a);
		}
		else
			ft_putchar(base[nb], a);
	}
}
