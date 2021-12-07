/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 12:25:23 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/20 18:43:56 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_ndisp(int x, int nbchar, int nbz, t_reponse *a)
{
	int	y;

	if (x < 0)
		nbchar--;
	while (nbchar-- > 0)
		ft_putchar(' ', a);
	if (x < 0)
	{
		ft_putchar('-', a);
		y = x * -1;
	}
	else
		y = x;
	while (nbz-- > 0)
		ft_putchar('0', a);
	ft_putnbrebase(y, a->base, a);
}

void	ft_specspe(char *test, t_reponse *a)
{
	a->spec = '0';
	while (test[a->x] == '-' || test[a->x] == '0')
	{
		if (test[a->x] == '-')
			a->spec = '-';
		a->x++;
	}
}

void	ft_ndispx(unsigned int y, int nbchar, int nbz, t_reponse *a)
{
	while (nbchar-- > 0)
		ft_putchar(' ', a);
	while (nbz-- > 0)
		ft_putchar('0', a);
	ft_putnbrebase(y, a->base, a);
}
