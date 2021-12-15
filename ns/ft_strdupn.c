/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 12:44:23 by niels             #+#    #+#             */
/*   Updated: 2021/12/12 20:05:50 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdupn(const char *s1)
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
