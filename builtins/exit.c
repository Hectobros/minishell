/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 08:44:39 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 10:25:12 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long double	ft_bigatoi(const char *str)
{
	int				x;
	int				com;
	long double		nb;

	if (str == NULL)
		return (0);
	x = 0;
	nb = 0;
	while ((str[x] > 8 && str[x] < 14)
		|| str[x] == 32)
		x++;
	com = x;
	if (str[x] == '+' || str[x] == '-')
		x++;
	while (str[x] > 47 && str[x] < 58)
	{
		nb = nb * 10 + (str[x] - 48);
		x++;
	}
	if (str[com] == '-')
		return (-nb);
	return (nb);
}

int	sizeoftab(char **cmd)
{
	int	x;

	x = 0;
	if (!cmd)
		return (x);
	while (cmd[x] != NULL)
		x++;
	return (x);
}

int	isnumeric(char *s)
{
	int	x;
	int	pivot;

	if (s == NULL)
		return (-1);
	x = 0;
	pivot = 0;
	if (s[x] == 45 || s[x] == 43)
		x++;
	while (s[x] && pivot != 1)
	{
		if (!(s[x] > 47 && s[x] < 58))
			pivot = 1;
		x++;
	}
	if (ft_bigatoi(s) > LONG_MAX || ft_bigatoi(s) < LONG_MIN)
		pivot = 1;
	return (pivot);
}

int	exit2(char **cmd)
{
	if (isnumeric(cmd[1]) != 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
		g_globa.herve = 2;
	}
	else
		g_globa.herve = (long long int)ft_bigatoi(cmd[1]) % 256;
	return (888);
}

int	exit42(char **cmd)
{
	int	x;

	printf("exit\n");
	x = sizeoftab(cmd);
	if (x == 1)
	{
		g_globa.herve = 0;
		return (888);
	}
	else if (x == 2)
		return (exit2(cmd));
	else
	{
		if (isnumeric(cmd[1]) != 0)
		{
			printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
			g_globa.herve = 2;
			return (888);
		}
		else
			printf("minishell: exit: too many arguments\n");
		g_globa.herve = 1;
		return (1);
	}
}
