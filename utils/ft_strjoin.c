/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:31:14 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 08:43:30 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*help_join(char const *s1, char const *s2, char **dst)
{
	int	size;
	int	i;
	int	j;

	i = 0;
	j = 0;
	size = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	dst[0] = malloc(sizeof(char) * size);
	if (dst[0] == NULL)
		return (NULL);
	while (s1[j])
		dst[0][i++] = s1[j++];
	j = 0;
	while (s2[j])
		dst[0][i++] = s2[j++];
	dst[0][i] = '\0';
	return (*dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;

	new = NULL;
	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	else
		help_join(s1, s2, &new);
	return (new);
}
