/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cconv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 12:25:23 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/20 18:30:21 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_cconv(va_list ap, t_reponse *a)
{
	char	x;

	x = (char)va_arg(ap, int);
	if (a->taille > 1)
		ft_displayc(x, a);
	else
		ft_putchar(x, a);
	return (0);
}

void	ft_displayc(char x, t_reponse *a)
{
	int		con;

	con = a->taille;
	if (a->spec == '-')
	{
		ft_putchar(x, a);
		while (con-- > 1)
			ft_putchar(' ', a);
	}
	else if (a->spec == 'N')
	{
		while (con-- > 1)
			ft_putchar(' ', a);
		ft_putchar(x, a);
	}
	else if (a->spec == '0')
	{
		while (con-- > 1)
			ft_putchar('0', a);
		ft_putchar(x, a);
	}
}
