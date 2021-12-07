/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 11:49:59 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/17 07:39:23 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		x;
	char	*ptr;

	if (s != NULL && (*f) != NULL)
	{
		x = (int)ft_strlen(s);
		ptr = (char *)malloc(sizeof(char) * (x + 1));
		if (!(ptr))
			return (NULL);
		x = 0;
		while (s[x])
		{
			ptr[x] = (*f)(x, s[x]);
			x++;
		}
		ptr[x] = '\0';
		return (ptr);
	}
	return (NULL);
}
