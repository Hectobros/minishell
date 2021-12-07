/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrspe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 11:43:49 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/20 18:54:57 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstrspe(char *s, t_reponse *a)
{
	int	x;

	if (s != NULL && s)
	{
		x = 0;
		while (s[x])
		{
			ft_putchar(s[x], a);
			x++;
		}
	}
}
