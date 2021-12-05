/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niels <niels@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 11:48:44 by nschmitt          #+#    #+#             */
/*   Updated: 2020/01/02 11:07:22 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			n;
	size_t			x;
	unsigned int	t;

	t = 0;
	n = ft_strlen(dst);
	x = ft_strlen(src);
	if (dstsize < n)
		return (x + dstsize);
	else
		x = x + n;
	while (src[t] && n < dstsize - 1)
	{
		dst[n] = src[t];
		t++;
		n++;
	}
	dst[n] = '\0';
	return (x);
}
