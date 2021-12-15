/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:17:57 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/15 11:54:02 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	remove_quote(char *str, char c)
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
	int	i;

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
	char	*tmp;

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

char	*quote_open(char *str, char c, int *quote)
{
	*quote = 1;
	while (*str && *str != c)
		str++;
	if (*str == c)
		*quote = 0;
	return (str);
}

int	check_open_quotes(char *str)
{
	int	quote;

	quote = 0;
	while (*str)
	{
		if (*str == '\'')
			str = quote_open(++str, '\'', &quote);
		if (*str == '"')
			str = quote_open(++str, '"', &quote);
		str++;
	}
	if (quote == 1)
		return (1);
	return (0);
}
