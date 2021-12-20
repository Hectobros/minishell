/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:29:51 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/19 17:14:55 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	len_dest(int n, size_t *p)
{
	int	r;

	r = 1;
	*p = 1;
	if (n < 0 || n == 0)
		r++;
	while (n != 0)
	{
		*p = *p * 10;
		n = n / 10;
		r++;
	}
	*p = *p / 10;
	return (r);
}

char	*ft_itoa(int n)
{
	char		*dest;
	int			i;
	size_t		multi;
	long int	nb;

	i = 0;
	nb = (long int)n;
	dest = malloc(sizeof(char) * len_dest(nb, &multi));
	if (!dest)
		return (NULL);
	if (nb == 0)
		dest[i++] = '0';
	else if (nb < 0)
	{
		dest[i++] = '-';
		nb = -nb;
	}
	while (multi >= 1)
	{
		dest[i++] = (nb / multi) + '0';
		nb = nb % multi;
		multi = multi / 10;
	}
	dest[i] = '\0';
	return (dest);
}
