/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 15:29:08 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/19 16:20:51 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	how_many_str(const char *s, char c, int *hm)
{
	*hm = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s != '\0')
		{
			(*hm)++;
			while (*s != c && *s != '\0')
				s++;
		}
	}
	if (*hm == 0)
		return (0);
	(*hm)++;
	return (1);
}

char	*get_str(const char *str, char c)
{
	const char	*tmp;
	char		*dst;
	int			size;
	int			i;

	i = 0;
	size = 0;
	tmp = str;
	while (*(tmp) && (*(tmp++) != c))
		size++;
	dst = malloc(sizeof(char) * (size + 1));
	if (!dst)
		return (NULL);
	while (*str && *str != c)
		dst[i++] = *(str++);
	dst[i] = '\0';
	return (dst);
}

char	**ft_split(const char *str, char c)
{
	int		n;
	int		hm;
	char	**dest;

	n = 0;
	if (!str)
		return (NULL);
	how_many_str(str, c, &hm);
	dest = malloc(sizeof(char *) * hm);
	if (!dest)
		return (NULL);
	while (n < (hm - 1))
	{
		while (*str && *str == c)
			str++;
		dest[n] = get_str(str, c);
		if (!dest[n])
			return (NULL);
		while (*str && *str != c)
			str++;
		n++;
	}
	dest[n] = NULL;
	return (dest);
}
