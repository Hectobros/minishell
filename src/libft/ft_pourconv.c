/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pourconv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 15:10:55 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/20 18:48:05 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pourconv(t_reponse *a)
{
	if (a->taille > 1)
		ft_displayc('%', a);
	else
		ft_putchar('%', a);
	return (0);
}
