/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:07:46 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 10:09:23 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	all_errors(t_mini *l, t_env *lenv, t_mini *tmp)
{
	if (l->fdout == -3)
		printf("minishell: %s: Is a directory\n", l->crashword);
	else if (l->fdout == -2 || l->fdin == -2)
		printf("minishell: %s: ambigous redirect\n", l->crashword);
	else if (l->fdout == -1 || l->fdin == -1)
		printf("minishell: %s: Permission denied\n", l->crashword);
	else if (l->fdin == -4)
		printf("minishell: %s: No such file or directory\n", l->crashword);
	ft_destroy(tmp);
	free_env(lenv);
	exit(1);
}

void	launch_children(t_mini *l, t_env *lenv, char **env, t_mini *tmp)
{
	int	saveout;

	rl_clear_history();
	ft_delsignal();
	if (l->fdout == -3 || l->fdout == -2 || l->fdout == -1
		|| l->fdin == -2 || l->fdin == -1 || l->fdin == -4)
		all_errors(l, lenv, tmp);
	saveout = dup(1);
	if (l->next)
		close(l->pipe[0]);
	if (l->fdin >= 0)
		dup2(l->fdin, 0);
	else if (l->prev)
		dup2(l->prev->pipe[0], 0);
	if (l->fdout >= 0)
		dup2(l->fdout, 1);
	else if (l->next)
		dup2(l->pipe[1], 1);
	run_command(l, lenv, env, saveout);
	close(saveout);
}

int	mini_exec(t_mini *l, t_env *lenv, char **env, t_mini *tmp)
{
	while (l && l->cmd)
	{
		if (l->next)
			pipe(l->pipe);
		l->pid = fork();
		if (l->pid == 0)
		{
			launch_children(l, lenv, env, tmp);
			ft_destroy(tmp);
			free_env(lenv);
			exit(127);
		}
		else if (l->pid < 0)
			return (1);
		else
			globa.pid = l->pid;
		if (l->prev)
			close(l->prev->pipe[0]);
		if (l->next)
			close(l->pipe[1]);
		l = l->next;
	}
	return (0);
}
