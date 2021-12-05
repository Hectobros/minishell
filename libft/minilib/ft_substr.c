/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:21:28 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/17 07:40:26 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (s != NULL)
	{
		i = 0;
		if (start >= ft_strlen(s) || len == 0)
			return (ft_strdup("\0"));
		ptr = (char *)malloc((len + 1) * sizeof(char));
		if (!(ptr))
			return (NULL);
		while (s[start + i] && i < len)
		{
			ptr[i] = s[start + i];
			i++;
		}
		ptr[i] = '\0';
		return (ptr);
	}
	return (NULL);
}
