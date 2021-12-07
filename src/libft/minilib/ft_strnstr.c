/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 11:57:57 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/17 07:22:35 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n;

	if (haystack == NULL || needle == NULL)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	n = ft_strlen(needle);
	while (*haystack && len-- >= n)
	{
		if (ft_strncmp(haystack, needle, n) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
