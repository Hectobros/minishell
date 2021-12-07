/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 16:34:37 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/20 18:50:37 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	ft_printf(const char *str, ...)
{
	int		x;
	char	*test;
	int		con;
	va_list	ap;

	x = 0;
	con = 0;
	test = (char *)str;
	va_start(ap, str);
	while (test[x])
	{
		if (test[x] != '%')
		{
			write(1, &test[x], 1);
			con++;
		}
		else
			x = ft_start(x, ap, test, &con);
		x++;
	}
	va_end(ap);
	return (con);
}

int	ft_start(int x, va_list ap, char *test, int *con)
{
	t_reponse	a;

	ft_maz(&a);
	a.x = x + 1;
	ft_reader(ap, test, &a);
	ft_etoile(ap, &a);
	*con = *con + a.con;
	return (a.y);
}

int	*ft_maz(t_reponse *a)
{
	a->spec = *"N";
	a->taille = -1;
	a->point = -1;
	a->precision = -1;
	a->convertion = 0;
	a->con = 0;
	a->base = NULL;
	return (0);
}

void	ft_etoile(va_list ap, t_reponse *a)
{
	if (a->convertion == 'c')
		ft_cconv(ap, a);
	else if (a->convertion == 'd' || a->convertion == 'i')
		ft_dconv(ap, a, "0123456789");
	else if (a->convertion == 's')
		ft_sconv(ap, a);
	else if (a->convertion == '%')
		ft_pourconv(a);
	else if (a->convertion == 'x')
		ft_xconv(ap, a, "0123456789abcdef");
	else if (a->convertion == 'X')
		ft_xconv(ap, a, "0123456789ABCDEF");
	else if (a->convertion == 'p')
		ft_pconv(ap, a);
	else if (a->convertion == 'u')
		ft_xconv(ap, a, "0123456789");
}
