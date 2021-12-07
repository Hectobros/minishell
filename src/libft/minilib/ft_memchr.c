/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 11:30:55 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/17 07:32:24 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int					x;
	unsigned char		*ptr;

	if (s == NULL)
		return (NULL);
	ptr = (unsigned char *)s;
	x = 0;
	while (n-- > 0)
	{
		if (ptr[x] == (unsigned char)c)
			return (ptr + x);
		x++;
	}
	return (NULL);
}
