/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:17:57 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/10 17:37:38 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *quote_open(const char *str, char c, int *quote)
{
	*quote = 1;
	while (*str && *str != c)
		str++;
	if (*str == c)
		*quote = 0;
	return (str);
}

int	check_open_quotes(const char *str)
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
