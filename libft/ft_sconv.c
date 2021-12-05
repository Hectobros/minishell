/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sconv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 18:24:17 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/20 19:37:00 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_sconv(va_list ap, t_reponse *a)
{
	char	*s;
	size_t	size;

	s = (char *)va_arg(ap, void *);
	if (s != NULL)
	{
		if (a->point == 1 && a->precision >= 0)
			size = t(((int)ft_strlen(s) >= a->precision),
					a->precision, (int)ft_strlen(s));
		else
			size = (int)ft_strlen(s);
		ft_displays(s, size, a->taille - size, a);
	}
	else
		ft_sconverror(a, "(null)", 0, 0);
	return (0);
}

void	ft_displays(char *s, int size, int nbchar, t_reponse *a)
{
	int	c;

	c = 0;
	if (a->spec == 'N')
	{
		while (nbchar-- > 0)
			ft_putchar(' ', a);
		while (s[c] && c < size)
		{
			ft_putchar(s[c], a);
			c++;
		}
	}
	else if (a->spec == '0')
	{
		while (nbchar-- > 0)
			ft_putchar('0', a);
		while (s[c] && c < size)
		{
			ft_putchar(s[c], a);
			c++;
		}
	}
	ft_displaysmoins(s, size, nbchar, a);
}

void	ft_displaysmoins(char *s, int size, int nbchar, t_reponse *a)
{
	int	c;

	c = 0;
	if (a->spec == '-' && s)
	{
		while (s[c] && c < size)
		{
			ft_putchar(s[c], a);
			c++;
		}
		while (nbchar-- > 0)
			ft_putchar(' ', a);
	}
}

void	ft_sconverror(t_reponse *a, char *error, int x, int con)
{
	if (a->precision < 6 && a->point == 1)
		x = a->taille - a->precision;
	else
		x = a->taille - 6;
	if (a->spec == 'N')
	{
		while (x > 0)
		{
			ft_putchar(' ', a);
			x = x - 1;
		}
	}
	while (error[con])
	{
		if (con < a->precision || a->point == -1)
			ft_putchar(error[con], a);
		con++;
	}
	if (a->spec == '-')
	{
		while (x-- > 0)
			ft_putchar(' ', a);
	}
}
