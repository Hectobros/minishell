/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:16:54 by nschmitt          #+#    #+#             */
/*   Updated: 2020/01/02 15:56:20 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		x;
	char	*ptr;

	if (s == NULL)
		return (NULL);
	x = 0;
	ptr = (char *)s;
	while (ptr[x])
		x++;
	while (x >= 0)
	{
		if (ptr[x] == c)
			return (ptr + x);
		x--;
	}
	return (NULL);
}
