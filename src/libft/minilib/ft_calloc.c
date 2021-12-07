/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:26:11 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/17 07:24:36 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	if (count != 0 && size != 0)
	{
		mem = malloc(count * size);
		if (!(mem))
			return (NULL);
		ft_bzero(mem, count * size);
		return (mem);
	}
	return (malloc(1));
}
