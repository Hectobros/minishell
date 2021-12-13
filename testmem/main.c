/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:22:38 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/13 17:08:14 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	int		size;
	char	*dest;
	int		i;

	size = ft_strlen(src) + 1;
	if ((dest = (char *)malloc(sizeof(char) * size)) == 0)
		return (0);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	if (dest == NULL)
		return (NULL);
	return (dest);
}

int		remove_quote(char *str, char c)
{
	char	*tmp;

	while (*str)
	{
		if (*str == c)
		{
			tmp = str;
			tmp++;
			while (*tmp)
				*str++ = *tmp++;
			*str = '\0';
			return (0);
		}
		str++;
	}
	return (0);
}

int	remove_both_quotes(char *tmp, char c)
{
	int i;

	i = 0;
	remove_quote(tmp, c);
	while (*tmp != c)
	{
		i++;
		tmp++;
	}
	remove_quote(tmp, c);
	return (i);
}

void	remove_quotes(t_content *lst)
{
	char *tmp;

	while (lst)
	{
		tmp = lst->content;
		while (*tmp)
		{
			if (*tmp == '"' || *tmp == '\'')
				tmp = tmp + remove_both_quotes(tmp, *tmp);
			else
				tmp++;
			
		}
		lst = lst->next;
	}
}

char	*re_alloc(char *buff, int hl, int limit)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * hl);
	if (!new)
		return (NULL);
	while (i < limit)
	{
		new[i] = buff[i];
		i++;
	}
	free(buff);
	return (new);
}

int main(void)
{
	char *test;
//	t_content	*lst;

//	lst = malloc(sizeof(t_content));
	test = ft_strdup("''on' va remove de la' mem''");
//	lst->content = test;

//	printf("%s\n", lst->content);
//	remove_quotes(lst);
//	printf("%s\n", test);
	test = re_alloc(test, 50, ft_strlen(test) + 1);
	free(test);


	return (0);
}
























