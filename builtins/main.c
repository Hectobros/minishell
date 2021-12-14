/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:14:02 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/14 17:14:18 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>

void	put_s(char *s)
{
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
}

void	putstr_and_s(char *message, char *s)
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

void	pwd42(char **cmd)
{
	char	*buf;

	if (cmd[1] && cmd[1][0] == '-' && cmd[1][1])
	{
		printf("pwd: %s: invalid option\n", cmd[1]);
//		exit(2);
	}
	buf = malloc(sizeof(char) * 4096);//valeur arbitraire
	if (!buf)
		exit(1);
	if (!getcwd(buf, 4097))
	{
		printf("getcwd: path too long");
		exit(3);
	}
	printf("%s\n", buf);
	free(buf);
//	exit(0);
}

void	cd_error(int i, char **cmd)
{
	if (i == 1)
		printf("cd: %s: File name too long\n", cmd[1]);
	else if (i == 2)
		printf("cd: %s: No such file or directory\n", cmd[1]);
	else if (i == 3)
		printf("cd: %s: Permission denied\n", cmd[1]);
	else if (i == 4)
		printf("cd: %s: Not a directory\n", cmd[1]);
	else if (i == 5)
		printf("cd: too many arguments\n");
//	exit(1);
}
void	cd42(char **cmd)
{
	if (!cmd[1])
		exit(0);
	if (strlen(cmd[1]) > 255)
		cd_error(1, cmd);
	if (cmd[2])
		cd_error(5, cmd);
	else if (access(cmd[1], F_OK))
		cd_error(2, cmd);
	else if (access(cmd[1], X_OK))
		cd_error(3, cmd);
	else if (chdir(cmd[1]))
		cd_error(4, cmd);
//	exit(0);
}

int	is_n_option(char *str)
{
	if (str[0] == '-' && str[1] == 'n' && !str[2])
		return (1);
	return (0);
}
void	echo42(char **cmd)
{
	int i;
	int	n;

	i = 1;
	n = 1;
	while (cmd[i] && is_n_option(cmd[i]))
	{
		n = 0;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		printf(" ");
		i++;
	}
	if (n)
		printf("\n");
//	exit(0);
}

int	main(int ac, char **av)
{
	DIR *d;
	struct dirent *sd;
	char		*rl;
	const char	*prompt;
	int			exit = 1;
	char		**cd;
	char		**pwd;
	char		**echo;
	(void)av;
	(void)ac;

	cd = malloc(sizeof(char*) * 5);
	pwd = malloc(sizeof(char*) * 5);
	echo = malloc(sizeof(char*) * 8);

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
		echo[0] = strdup("echo");
		echo[1] = strdup("-n");
		echo[2] = strdup("-n");
		echo[3] = strdup("brat");
		echo[4] = strdup("-n");
		echo[5] = NULL;
		env[0] = strdup("env");
		env[1] = NULL;

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
//			echo42(echo);
			//cd42(cd);
		


		//		exit = 0;
	}
	return (0);
}
