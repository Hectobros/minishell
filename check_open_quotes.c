/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:17:57 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/09 10:03:32 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *quote_open(char *str, char c, int *quote)
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
