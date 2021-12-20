/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:14:02 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/16 16:14:02 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_s(char *s)
{
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
}

void	putstr_and_s(const char *message, char *s)
{
	while (*message)
	{
		while (*message != '%' && *message)
			write(1, message++, 1);
		if (*message == '%' && *(message + 1) && *(message + 1) == 's')
		{
			message = message + 2;
			put_s(s);
		}
	}
}

void	write_error(const char *err, char *s)
{
	putstr_and_s(err, s);
}
