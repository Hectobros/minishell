/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 09:50:47 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global globa;

void	print_env(t_env *lenv)//DEL
{
	while (lenv)
	{
		printf("%s=%s\n", lenv->name, lenv->value);
		lenv = lenv->next;
	}
}

void	print_lst(t_content *lst)//DEL
{
	while (lst)
	{
		printf("token:%d  ", lst->token);
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}








void	all_errors(t_mini *l, t_mini *tmp, t_env *lenv)
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
void	mini_exec(t_mini *l, t_env *lenv, char **env)
{
	t_mini	*tmp;
	int	saveout;

	tmp = l;
	while (l && l->cmd)
	{
		if (l->next)
			pipe(l->pipe);
		l->pid = fork();
		//		if (l->pid  < 0) ->Error
		if (l->pid == 0)
		{
			rl_clear_history();
			ft_delsignal();
			//			if (!l->prev       ---> why added ? fail ? are u dump ?)
			if (l->fdout == -3 || l->fdout == -2 || l->fdout == -1 
					|| l->fdin == -2 || l->fdin == -1 || l->fdin == -4)
				all_errors(l, tmp, lenv);
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
			ft_destroy(tmp);
			free_env(lenv);
			exit(127);
		}
		else
			globa.pid = l->pid;
		if (l->prev)
			close(l->prev->pipe[0]);
		if (l->next)
			close(l->pipe[1]);
		l = l->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_content	*lst;
	t_env		*lenv;
	char		*rl;
	const char	*prompt;
	t_mini		*com;
	int			ret;
	(void)ac; (void)av;
	int			exit = 1;

	globa.herve = 0;
	com = NULL;
	lenv = NULL;
	create_env_lst(&lenv, env);
	//	print_env(lenv);
	prompt = "minishell$ ";
	while (exit)
	{
		globa.pid = -1;
		lst = NULL;
		ft_setsignal();
		rl = readline(prompt);
		if (rl == NULL)
		{
			rl_clear_history();
			free_env(lenv);
			printf("exit\n");
			return(0);
		}
		rl = pipe_at_end(rl);
		if (ft_strlen(rl) != 0)
			add_history(rl);
		if (!make_token(rl, &lst, lenv))
		{
			//		print_lst(lst);
			com = ft_buildpipe(lst, lenv);
			add_prev_mini(com);

			free_content_lst(lst);
			free(rl);

			//		if (com != NULL)
//						ft_printcomm(com);

			if (len_mini(com) == 1 && is_parent(com))
			{
				ret = dad_is_running(com, lenv);
				if (ret == 888)
					exit = 0;
				else
					globa.herve = ret;
			}
			else
			{
				mini_exec(com, lenv, env);
				wait_all(com);
			}
			ft_destroy(com);
		}
//		exit = 0;
		//		printf("glo:%d\n", globa.herve);
	}
	rl_clear_history();
	free_env(lenv);
	return (globa.herve);
}
