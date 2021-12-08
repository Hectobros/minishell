/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/08 17:47:48 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_open_quotes(char *str)
{
	int	quote;

	quote = 0;
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			quote = 1;
			while (*str && *str != '\'')
				str++;
			if (*str == '\'')
				quote = 0;
		}
		if (*str == '"')
		{
			str++;
			quote = 1;
			while (*str && *str != '"')
				str++;
			if (*str == '"')
				quote = 0;
		}
		str++;
	}
	if (quote == 1)
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	int		ret;
//	char	*line;
//	const char	*prompt;

	if (ac < 2)
		return (0);
	(void)av;
	(void)ret;
//	prompt = "";
	printf("%s\n", readline("jvermeer@e3r2p18:~/Desktop/minishell$"));

/*	ret = check_open_quotes(av[1]);
	if (ret)
		printf("fail\n");
	else
		printf("ok\n");
		*/
	return (0);
}
