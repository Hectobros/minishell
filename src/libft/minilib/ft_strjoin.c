/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 17:49:31 by niels             #+#    #+#             */
/*   Updated: 2021/11/17 22:47:46 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;

	if (s1 != NULL && s2 != NULL)
	{
		s1_len = ft_strlen(s1);
		s2_len = ft_strlen(s2);
		ptr = (char *)malloc((s1_len + s2_len + 1) + sizeof(char));
		if (!(ptr))
			return (NULL);
		ft_strlcpy(ptr, s1, s1_len + 1);
		ft_strlcat(ptr, s2, s2_len + s1_len + 1);
		return (ptr);
	}
	return (NULL);
}
