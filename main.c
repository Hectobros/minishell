/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 09:36:21 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global globa;

void	print_env(t_env *lenv)
{
	while (lenv)
	{
		printf("%s=%s\n", lenv->name, lenv->value);
		lenv = lenv->next;
	}
}

void	print_lst(t_content *lst)
{
	while (lst)
	{
		printf("token:%d  ", lst->token);
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}

int	is_builtin(t_mini *l)
{
	if (!l->cmd)
		return (0);
	else if (str_comp(l->cmd[0], "echo"))
		return(1);
	else if (str_comp(l->cmd[0], "cd"))
		return(1);
	else if (str_comp(l->cmd[0], "pwd"))
		return(1);
	else if (str_comp(l->cmd[0], "env"))
		return(1);
	else if (str_comp(l->cmd[0], "export"))
		return(1);
	else if (str_comp(l->cmd[0], "unset"))
		return(1);
	else if (str_comp(l->cmd[0], "exit"))
		return(1);
	return(0);
}

int	is_parent(t_mini *l)
{
	if (!l->cmd)
		return (0);
	else if (str_comp(l->cmd[0], "cd"))
		return(1);
	else if (str_comp(l->cmd[0], "export"))
		return(1);
	else if (str_comp(l->cmd[0], "unset"))
		return(1);
	else if (str_comp(l->cmd[0], "exit"))
		return(1);
	return(0);
}

int	len_mini(t_mini *com)
{
	int	len;

	len = 0;
	while (com)
	{
		len++;
		com = com->next;
	}
	return(len);
}
void	add_prev_mini(t_mini *com)
{
	t_mini	*tmp;

	tmp = NULL;
	while (com)
	{
		com->prev = tmp;
		tmp = com;
		com = com->next;
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
void	wait_all(t_mini *l)
{
	int	status;

	while (l && l->cmd)
	{
		waitpid(l->pid, &status, 0);
		if (WIFEXITED(status))
			globa.herve = (WEXITSTATUS(status) % 256);
		l = l->next;
	}
}

int	dad_is_running(t_mini *l, t_env *lenv)
{
	int	ret;

	ret = 0;
	if (!l->cmd)
		ret = 0;
	else if (str_comp(l->cmd[0], "cd"))
		ret = cd42(l->cmd, lenv);
	else if (str_comp(l->cmd[0], "export"))
		ret = export42(l->cmd, &lenv);
	else if (str_comp(l->cmd[0], "unset"))
		ret = unset42(l->cmd, &lenv);
	else if (str_comp(l->cmd[0], "exit"))
		ret = exit42(l->cmd);
	return (ret);
}

int	is_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
		i++;
	while (i > 0 && str[i] == ' ')
		i--;
	if(i > 0 && str[i] == '|')
		return (1);
	return (0);
}

char	*pipe_at_end(char *rl)
{
	char	*rl2;
	char	*tmp;

	if (!is_pipe(rl))
		return (rl);
	rl2 = readline(">");
	if (rl2 == NULL)
		return (rl);
	while(*rl2 == '\0' || is_pipe(rl2))
	{
		tmp = rl;
		rl = ft_strjoin(rl, rl2);
		if (!rl)
			return(NULL);
		free(tmp);
		free(rl2);
		rl2 = readline(">");
		if (rl2 == NULL)
			return (rl);
	}
	tmp = rl;
	rl = ft_strjoin(rl, rl2);
	free(tmp);
	free(rl2);
	return (rl);
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
