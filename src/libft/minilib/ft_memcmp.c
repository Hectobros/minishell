/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 11:33:02 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/17 07:32:44 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				x;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (s1 != NULL && s2 != NULL && n != 0 && s1 != s2)
	{
		ptr1 = (unsigned char *)s1;
		ptr2 = (unsigned char *)s2;
		x = 0;
		while (n-- > 0)
		{
			if (ptr1[x] != ptr2[x])
				return ((int)(ptr1[x] - ptr2[x]));
			x++;
		}
	}
	return (0);
}
