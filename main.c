/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/18 20:20:25 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global globa;

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

int	is_parent(t_mini *l)
{
	if (str_comp(l->cmd[0], "cd"))
		return(1);
	else if (str_comp(l->cmd[0], "export"))
		return(1);
	else if (str_comp(l->cmd[0], "unset"))
		return(1);
	else if (str_comp(l->cmd[0], "exit"))
		return(1);
	return(0);
}

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

/*
void	put_s(char *s)
{
	while (*s)
	{
		write(2, s, 1);
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
*/



char	*make_path(const char *cmd, const char *path)
{
	char *buff;
	int	i;

	i = 0;
	buff = malloc(sizeof(char) * (2 + ft_strlen(cmd) + ft_strlen(path)));
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
	{
		rl_clear_history();
		free_env(lenv);
		ft_destroy(l);
		exit(ret);
	}
	return (ret);
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

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	run_command(t_mini *l, t_env *lenv, char **env)
{
	char	**path;
	char	*buff;
	int		i;

	i = 0;
	if (is_builtin(l))
		run_builtin(l, lenv, 1);
	path = get_path(lenv);

	buff = make_path(l->cmd[0], "");
	if (!buff)
		exit(33);
	execve(buff, l->cmd, env);
	free(buff);

	while (path && path[i])
	{
		buff = make_path(l->cmd[0], path[i]);
		if (!buff)
			exit(33);
		execve(buff, l->cmd, env);//ENV ?
		free(buff);
		i++;
	}
	free_path(path);
	printf("%s: command not found\n", l->cmd[0]);
	exit(1);
}

void	all_errors(int fdin, int fdout, t_mini *l)
{
//	char *test;

//	test = strerror(errno);
	if (fdout == -3)
	{

		printf("bash: %s: Is a directory\n", l->crashword);
	//	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	//	exit(errno);
		exit(1);
	}
	else if (fdout == -2 || fdin == -2)
	{
		printf("bash: %s: ambigous redirect\n", l->crashword);
		exit(1);
	}
	else if (fdout == -1 || fdin == -1)
	{
		printf("bash: %s: Permission denied\n", l->crashword);
		exit(1);
	}
	else if (fdin == -4)
	{
		printf("bash: %s: No such file or directory\n", l->crashword);
		exit(1);
	}
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
			ft_delsignal();
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

	while (l)
	{
		wait(&status);
		l = l->next;
	}
}

int	dad_is_running(t_mini *l, t_env *lenv)
{
	int	ret;

	ret = 0;
	if (str_comp(l->cmd[0], "cd"))
		ret = cd42(l->cmd, lenv);
	else if (str_comp(l->cmd[0], "export"))
		ret = export42(l->cmd, &lenv);
	else if (str_comp(l->cmd[0], "unset"))
		ret = unset42(l->cmd, &lenv);
//	else if (str_comp(l->cmd[0], "exit"))
//		ret = exit42(l->cmd, &lenv);
	return (ret);
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

	globa.herve = 0;
	dol_inter = 0;
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
		//HERE add end |
		if (rl == NULL)
			return(0);
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

		free_content_lst(lst);
		free(rl);

//		if (com != NULL)
//			ft_printcomm(com);
		
		if (len_mini(com) == 1 && is_parent(com))
		{
			dad_is_running(com, lenv);
		}
		else
		{
			mini_exec(com, lenv, env);
			wait_all(com);
		}
		ft_destroy(com);
//		exit = 0;
	}
	rl_clear_history();
	free_env(lenv);
	return (0);
}
