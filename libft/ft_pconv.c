/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pconv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 11:20:26 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/20 18:47:51 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pconv(va_list ap, t_reponse *a)
{
	unsigned long	y;
	void			*x;

	y = 0;
	x = va_arg(ap, void *);
	y = (unsigned long)x;
	ft_displayp(y, a);
}

void	ft_putp(unsigned long x, char *base, t_reponse *a)
{
	if (x > 15)
	{
		ft_putnbrebase(x / 16, base, a);
		ft_putchar(base[x % 16], a);
	}
	else
		ft_putchar(base[x], a);
}

void	ft_displayp(unsigned long y, t_reponse *a)
{
	int	con;

	con = a->taille;
	if (a->spec == '-')
	{
		ft_putstrspe("0x", a);
		ft_putp(y, "0123456789abcdef", a);
		while (con-- > ft_sizenbx(y, 16) + 2)
			ft_putchar(' ', a);
	}
	else if (a->spec == 'N')
	{
		while (con-- > ft_sizenbx(y, 16) + 2)
			ft_putchar(' ', a);
		ft_putstrspe("0x", a);
		ft_putp(y, "0123456789abcdef", a);
	}
	else if (a->spec == '0')
	{
		while (con-- > ft_sizenbx(y, 16) + 2)
			ft_putchar('0', a);
		ft_putstrspe("0x", a);
		ft_putp(y, "0123456789abcdef", a);
	}
}
