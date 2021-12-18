/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 17:57:10 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/18 18:01:08 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int ac, char **av, char **env)
{
	char	**cat;
	int		pid;

	(void)ac;
	(void)av;
	cat = malloc(sizeof(char *) * 5);
	cat[0] = strdup("cat");
	cat[1] = strdup("yoooo");
	cat[2] = NULL;

	pid = fork();
	if (!pid)
	{
		execve("/usr/bin/cat", cat, env);
	}
	return (0);
}
