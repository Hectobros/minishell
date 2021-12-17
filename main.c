/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/17 11:06:29 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
/*
   void	close_heredoc_pipes(t_content *lst)//      <---- If parsing failed
   {
   while (lst)
   {
   if (lst->token == 5)
   {
   close(lst->pfd[0]);
   }
   lst = lst->next;
   }
   }
 */

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




char	*make_path(const char *cmd, const char *path)
{
	char *buff;
	int	i;

	i = 0;
	buff = malloc(sizeof(char) * (1 + ft_strlen(cmd) + ft_strlen(path)));
	if (!buff)
		return (NULL);
	while (*path)
		buff[i++] = *path++;
	buff[i++] = '/';
	while (*cmd)
		buff[i++] = *cmd++;
	buff[i] = '\0';
	return (buff);
}

void	run_command(t_mini *l, t_env *lenv, char **env)
{
	char	**path;
	char	*buff;

	path = NULL;
	while (lenv)
	{
		if (str_comp(lenv->name, "PATH"))
		{
			path = ft_split(lenv->value, ':');
			if (!path)
				exit(33);
		}
		lenv = lenv->next;
	}
	while (path && *path)
	{
		buff = make_path(l->cmd[0], *path);
		if (!buff)
			exit(33);
		execve(buff, l->cmd, env);//ENV ?
		free(buff);
		path++;
	}
	printf("%s: command not found\n", l->cmd[0]);
	exit(1);
}

void	mini_exec(t_mini *l, t_env *lenv, char **env)
{
	while (l)
	{
		if (l->prev)
			close(l->pin[1]);
		if (l->next)
			pipe(l->pout);
		l->pid = fork();

		if (l->pid == 0)
		{
			if (l->fdin >= 0)
			{
				dup2(l->fdin, 0);
				if (l->prev)
					close(l->pin[0]);
			}
			else if (l->prev)
				dup2(l->pin[0], 0);
			if (l->fdout >= 0)
			{
				dup2(l->fdout, 1);
				close(l->pout[1]);
			}
			else if (l->next)
				dup2(l->pout[1], 1);

			run_command(l, lenv, env);
		}
		l = l->next;
	}
}

void	wait_all(t_mini *l)
{
	int	status;

	while (l)
	{
		waitpid(l->pid, &status, 0);
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
	(void)ac; (void)av;
	int			exit = 1;

	com = NULL;
	lenv = NULL;
	create_env_lst(&lenv, env);
	//	print_env(lenv);
	prompt = "minishell$ ";
	while (exit)
	{
		lst = NULL;
		rl = readline(prompt);
		if (ft_strlen(rl) != 0)
			add_history(rl);
		if (make_token(rl, &lst, lenv))
		{
			printf("Error\n");
			return (1);
		}
//		print_lst(lst);
		com = ft_buildpipe(lst, lenv);
		add_prev_mini(com);
		if (com != NULL)
			ft_printcomm(com);

		mini_exec(com, lenv, env);
		wait_all(com);

		free(rl);
		free_content_lst(lst);
//		exit = 0;
	}
	free_env(lenv);
	return (0);
}
