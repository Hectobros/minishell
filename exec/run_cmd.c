/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:34:17 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 09:40:35 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*make_path(const char *cmd, const char *path)
{
	char	*buff;
	int		i;

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

void	run_builtin(t_mini *l, t_env *lenv)
{
	int	ret;

	ret = 0;
	if (!l->cmd)
		ret = 0;
	else if (str_comp(l->cmd[0], "echo"))
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
	free_env(lenv);
	ft_destroy(l);
	exit(ret);
}

char	**get_path(t_env *lenv)
{
	char	**path;

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
		path = malloc(sizeof(char *) * 2);
		if (!path)
			exit(33);
		path[0] = ft_strdup("\0");
		path[1] = NULL;
		if (!path[0])
			exit(33);
	}
	return (path);
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

void	run_command(t_mini *l, t_env *lenv, char **env, int saveout)
{
	char	**path;
	char	*buff;
	int		i;

	i = 0;
	if (is_builtin(l))
		run_builtin(l, lenv);
	path = get_path(lenv);
	execve(l->cmd[0], l->cmd, env);
	while (path && path[i])
	{
		buff = make_path(l->cmd[0], path[i]);
		if (!buff)
			exit(33);
		execve(buff, l->cmd, env);
		free(buff);
		i++;
	}
	free_path(path);
	dup2(saveout, 1);
	close(saveout);
	printf("%s: command not found\n", l->cmd[0]);
}
