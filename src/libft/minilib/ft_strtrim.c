/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:17:36 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/17 07:39:51 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_cinset(const char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	len;

	if (s1 != NULL && set != NULL)
	{
		i = 0;
		len = ft_strlen(s1);
		while (ft_cinset(s1[i], set))
			i++;
		while (ft_cinset(s1[len - 1], set) && len > 1)
			len--;
		if (len == 1)
			return (ft_strdup("\0"));
		return (ft_substr(s1, i, len - i));
	}
	return (ft_strdup("\0"));
}
