/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 19:46:49 by niels             #+#    #+#             */
/*   Updated: 2021/11/17 07:37:06 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbmot(const char *s, char c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 1;
	while (s[n])
	{
		if ((s[n] == c && s[n - 1] != c && s[n + 1]) || (s[n] != c && s[n + 1]
				== '\0'))
			i++;
		n++;
	}
	return (i);
}

char	*extract_word(const char *s, char c)
{
	int	fin;

	fin = 0;
	while (s[fin] && s[fin] != c)
		fin++;
	return (ft_substr(s, 0, fin));
}

char	**ft_split(const char *s, char c)
{
	char	**tab;
	size_t	x;
	size_t	n;

	if (s != NULL && *s != 0)
	{
		n = 0;
		x = ft_nbmot(s, c);
		tab = malloc((x + 1) * sizeof(char *));
		if (!(tab))
			return (NULL);
		while (n < x && *s)
		{
			while (*s == c)
				s++;
			tab[n] = extract_word(s, c);
			s = ft_strchr(s, c);
			n++;
		}
		tab[n] = NULL;
		return (tab);
	}
	return ((char **)ft_calloc(2, sizeof(char *)));
}
