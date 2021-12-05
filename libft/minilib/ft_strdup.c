/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 12:44:23 by niels             #+#    #+#             */
/*   Updated: 2021/11/17 07:37:39 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	n;

	if (s1 == NULL)
		return (NULL);
	ptr = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!(ptr))
		return (NULL);
	n = ft_strlen(s1);
	ft_memmove(ptr, s1, n + 1);
	return (ptr);
}
