/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:39:34 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 10:39:35 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	routine(int sig)
{
	if (g_globa.pid != -1)
	{
		g_globa.herve = 130;
		kill(g_globa.pid, sig);
		g_globa.pid = -1;
		printf("\n");
	}
	else if (g_globa.pid)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	rout(int sig)
{
	if (g_globa.pid != -1)
	{
		g_globa.herve = 131;
		kill(g_globa.pid, sig);
		printf("Quit (core dumped)\n");
		g_globa.pid = -1;
	}
	else
		write(1, "\b\b  \b\b", 6);
	(void)sig;
}

void	ft_setsignal(void)
{
	signal(SIGINT, &routine);
	signal(SIGQUIT, &rout);
}

void	ft_delsignal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
