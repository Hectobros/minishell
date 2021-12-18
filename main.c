/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/18 12:44:17 by jvermeer         ###   ########.fr       */
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

int	write_error(const char *err, char *s)
{
	putstr_and_s(err, s);
	//exit(1);
	return (1);
}

void	all_errors(int fdin, int fdout, t_mini *l)
{
	if (fdout == -3)
		write_error("bash: %s: Is a directory\n", l->crashword);
	else if (fdout == -2 || fdin == -2)
		write_error("bash: %s: ambigous redirect\n", l->crashword);
	else if (fdout == -1 || fdin == -1)
		write_error("bash: %s: Permission denied\n", l->crashword);
	else if (fdin == -4)
		write_error("bash: %s: No such file or directory\n", l->crashword);
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

int	run_builtin(t_mini *l, t_env *lenv, int ex)
{
	int	ret;

	if (str_comp(l->cmd[0], "echo"))
		ret = echo42(l->cmd);
	else if (str_comp(l->cmd[0], "cd"))
		ret = cd42(l->cmd, lenv);
	else if (str_comp(l->cmd[0], "pwd"))
		ret = pwd42(l->cmd);
	else if (str_comp(l->cmd[0], "env"))
		ret = env42(l->cmd, lenv);
	else if (str_comp(l->cmd[0], "export"))
		ret = export42(l->cmd, &lenv);
	else if (str_comp(l->cmd[0], "unset"))
		ret = unset42(l->cmd, &lenv);
	if (ex)
		exit(ret);
	return (ret);
}

int	is_builtin(t_mini *l)
{
	if (str_comp(l->cmd[0], "echo"))
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

char 	**get_path(t_env *lenv)
{
	char **path;

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
	if (!path)
	{
		path = malloc(sizeof(char*) * 2);
		if (!path)
			exit(33);
		path[0] = ft_strdup("\0");
		path[1] = NULL;
		if (!path[0])
			exit(33);
	}
	return(path);
}

void	run_command(t_mini *l, t_env *lenv, char **env)
{
	char	**path;
	char	*buff;

	if (is_builtin(l))
		run_builtin(l, lenv, 1);
	path = get_path(lenv);
	buff = make_path(l->cmd[0], "");
	if (!buff)
		exit(33);
	execve(buff, l->cmd, env);//ENV ?
	while (path && *path)
	{
		buff = make_path(l->cmd[0], *path);
		if (!buff)
			exit(33);
		execve(buff, l->cmd, env);//ENV ?
		free(buff);
		path++;
	}
	free(buff);
	write_error("%s: command not found\n", l->cmd[0]);
}

void	mini_exec(t_mini *l, t_env *lenv, char **env)
{
	while (l)
	{
		if (l->next)
			pipe(l->pipe);
		l->pid = fork();
//		if (l->pid  < 0) ->Error
		if (l->pid == 0)
		{
			if (!l->prev)
				all_errors(l->fdin, l->fdout, l);
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
			run_command(l, lenv, env);
		}
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

	while (l)
	{
		waitpid(0, &status, 0);
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
	int	dol_inter;

	dol_inter = 0;
	com = NULL;
	lenv = NULL;
	create_env_lst(&lenv, env);
//	print_env(lenv);
	prompt = "minishell$ ";
	while (exit)
	{
		lst = NULL;
		rl = readline(prompt);
		//HERE add end |
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
//		if (com != NULL)
//			ft_printcomm(com);
		
		if (len_mini(com) == 1 && is_builtin(com))
			run_builtin(com, lenv, 0);
		else
			mini_exec(com, lenv, env);
		wait_all(com);

		free(rl);
		free_content_lst(lst);
//		exit = 0;
	}
	rl_clear_history();
	free_env(lenv);
	ft_destroy(com);
	return (0);
}
