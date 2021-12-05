/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niels <niels@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:32:56 by nschmitt          #+#    #+#             */
/*   Updated: 2019/12/28 17:47:18 by niels            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char const *src, size_t dstsize)
{
	unsigned int	n;
	size_t			con;

	con = 0;
	n = 0;
	while (src[con] != '\0')
		con++;
	if (dstsize == 0)
	{
		return (con);
	}
	while (src[n] != '\0' && n < dstsize - 1)
	{
		dest[n] = src[n];
		n++;
	}
	dest[n] = '\0';
	return (con);
}
