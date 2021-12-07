/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 12:16:18 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/17 07:26:20 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_long(int x)
{
	int	n;

	n = 0;
	if (x == 0)
		n = 1;
	if (x < 0)
		n = 1;
	while (x != 0)
	{
		x = x / 10;
		n++;
	}
	return (n);
}

void	ft_cas(char *ptr)
{
	ptr[0] = '-';
	ptr[1] = '2';
	ptr[2] = '1';
	ptr[3] = '4';
	ptr[4] = '7';
	ptr[5] = '4';
	ptr[6] = '8';
	ptr[7] = '3';
	ptr[8] = '6';
	ptr[9] = '4';
	ptr[10] = '8';
}

void	ft_ecriture(char *ptr, int nb, int index)
{
	char	c;

	if (nb == -2147483648)
	{
		ft_cas(ptr);
		return ;
	}
	if (nb < 0)
	{
		ptr[0] = '-';
		nb = nb * -1;
	}
	if (nb > 9)
	{
		c = nb % 10 + '0';
		nb = nb / 10;
		index = index - 1;
		ft_ecriture(ptr, nb, index);
		ptr[index + 1] = c;
	}
	else
		ptr[index] = nb + '0';
}

char	*ft_itoa(int n)
{
	int		l;
	char	*ptr;

	l = ft_long(n);
	ptr = (char *)malloc(sizeof(char) * (l + 1));
	if (!(ptr))
		return (NULL);
	ft_ecriture(ptr, n, l - 1);
	ptr[l] = '\0';
	return (ptr);
}
