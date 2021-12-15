/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:14:02 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/15 18:05:14 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../minishell.h"

void	pwd42(char **cmd)
{
	char	*buf;

	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1])
	{
		putstr_and_s("pwd: %s: invalid option\n", cmd[1]);
//		putstr_and_s("pwd: usage: pwd [-LP]\n");
//		exit(2);
	}
	buf = malloc(sizeof(char) * 4096);//valeur arbitraire
	if (!buf)
		exit(1);
	if (!getcwd(buf, 4097))
	{
		putstr_and_s("getcwd: path too long", NULL);
		exit(3);
	}
	putstr_and_s("%s\n", buf);
	free(buf);
//	exit(0);
}

void	cd42(char **cmd)
{
	if (!cmd[1])
		exit(0);
	if (strlen(cmd[1]) > 255)
		write_error("cd: %s: File name too long\n", cmd[1]);
	if (cmd[2])
		write_error("cd: too many arguments\n", NULL);
	else if (access(cmd[1], F_OK))
		write_error("cd: %s: No such file or directory\n", cmd[1]);
	else if (access(cmd[1], X_OK))
		write_error("cd: %s: Permission denied\n", cmd[1]);
	else if (chdir(cmd[1]))
		write_error("cd: %s: Not a directory\n", cmd[1]);
//	exit(0);
}


int	main(int ac, char **av, char **env)
{
	DIR *d;
	struct dirent *sd;
	char		*rl;
	const char	*prompt;
	int			exit = 1;
	char		**cd;
	char		**pwd;
	(void)av;
	(void)env;
	(void)ac;

	cd = malloc(sizeof(char*) * 5);
	pwd = malloc(sizeof(char*) * 5);
	prompt = "builtin: ";
	while (exit)
	{
		rl = readline(prompt);
		cd[0] = strdup("cd");
		cd[1] = rl;
		cd[2] = NULL;
		pwd[0] = strdup("pwd");
		pwd[1] = strdup("-fefe");
		pwd[2] = NULL;
		if (rl[0] == 'p' && rl[1] == 'w' && rl[2] == 'd')
			pwd42(pwd);
		else if (rl[0] == 'l' && rl[1] == 's')
		{
			d = opendir(".");
			while ((sd = readdir(d)))
				printf("%s  ", sd->d_name);
			printf("\n");
		}
		else
			cd42(cd);
		//exit = 0;
	}
	return (0);
}