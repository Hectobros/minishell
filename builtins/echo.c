/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:14:02 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 08:31:58 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_n_option(char *str)
{
	if (str[0] == '-' && str[1] == 'n' && !str[2])
		return (1);
	return (0);
}

int	echo42(char **cmd)
{
	int	i;
	int	n;

	i = 1;
	n = 1;
	while (cmd[i] && is_n_option(cmd[i]))
	{
		n = 0;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (n)
		printf("\n");
	return (0);
}
