/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:14:02 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 08:31:38 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd42(char **cmd)
{
	char	*buf;

	buf = NULL;
	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1] &&
			(cmd[1][1] != '-' || cmd[1][2]))
	{
		printf("pwd: %s: invalid option\n", cmd[1]);
		return (2);
	}
	buf = malloc(sizeof(char) * 4097);
	if (!buf)
		return (33);
	if (!getcwd(buf, 2096))
	{
		printf("getcwd: path too long\n");
		return (3);
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}

int	chdir_to_home(t_env *lst)
{
	while (lst)
	{
		if (str_comp(lst->name, "HOME"))
		{
			chdir(lst->value);
			return (0);
		}
		lst = lst->next;
	}
	return (1);
}

int	cd42(char **cmd, t_env *lst)
{
	struct stat	st;

	if (!cmd[1])
	{
		chdir_to_home(lst);
		return (0);
	}
	stat(cmd[1], &st);
	if (strlen(cmd[1]) > 255)
		printf("minishell: cd: %s: File name too long\n", cmd[1]);
	else if (cmd[2])
		printf("minishell: cd: too many arguments\n");
	else if (access(cmd[1], F_OK))
		printf("minishell: cd: %s: No such file or directory\n", cmd[1]);
	else if (!S_ISDIR(st.st_mode))
		printf("minishell: cd: %s: Not a directory\n", cmd[1]);
	else if (chdir(cmd[1]))
		printf("minishell: cd: %s: Permission denied\n", cmd[1]);
	else
		return (0);
	return (1);
}
