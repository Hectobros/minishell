/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmoven.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 11:39:07 by nschmitt          #+#    #+#             */
/*   Updated: 2021/12/12 20:18:54 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*source;

	if (dst != src)
	{
		dest = (unsigned char *)dst;
		source = (unsigned char *)src;
		if (dest > source)
		{
			i = len + 1;
			while (--i > 0)
				dest[i - 1] = source[i - 1];
		}
		else
		{
			i = -1;
			while (++i < len)
				dest[i] = source[i];
		}
		return (dst);
	}
	return (NULL);
}
