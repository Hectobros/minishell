/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 14:07:24 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/15 18:58:27 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *src)
{
	int		size;
	char	*dest;
	int		i;

	size = ft_strlen(src) + 1;
	dest = malloc(sizeof(char) * size);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	if (dest == NULL)
		return (NULL);
	return (dest);
}


/*
void	read_heredoc(t_content *lst)
{
	while (lst)
	{
		if (lst->token == 5)
			test_inside_fd(lst->pfd);
		lst = lst->next;
	}
}
*/



int		str_cmp(const char *line, const char *match)
{
	while (*line && *match)
	{
		if (*line != *match)
			return (1);
		line++;
		match++;
	}
	if (*line != *match)
		return (1);
	return (0);
}

void	write_in_fd(const char *line, int fd, int *psize)
{
	while (*line)
	{
		write(fd, line, 1);
		line++;
		(*psize)++;
	}
	write(fd, "\n", 1);
	(*psize)++;
}

void	create_double(int fdp[2], const char *match, int *psize)
{
	char	*line;
	char	tmp[1];

	while (*psize)
	{
		read(fdp[0], tmp, 1);
		(*psize)--;
	}
	line = readline(">");
	while (str_cmp(line, match))
	{
		write_in_fd(line, fdp[1], psize);
		line = readline(">");
	}
}








void	test_inside_fd(int pfd[2])
{
	char	**test;
	int		pid;

	test = malloc(sizeof(char*) * 2);

	test[0] = ft_strdup("cat"); 
	test[1] = NULL;
	pid = fork();
	if (pid == 0)
	{
		close(pfd[1]);
		dup2(pfd[0], 0);
		execve("/usr/bin/cat", test, NULL);
	}
	free(test);
	waitpid(0, NULL, 0);
}

void	test_pipe(int fdp[2])
{
	write(fdp[1], "e", 1);
}

int	main(int ac, char **av, char **envp)
{
//	char	**test;
	int		fdp[2];
	(void)ac;
	(void)av;
	(void)envp;
//	printf("%d\n", access("$_", F_OK));


	pipe(fdp);
	test_pipe(fdp);
	printf("HERE\n");
	test_inside_fd(fdp);
	printf("HERE\n");
	/*
	int		psize = 0;
	create_double(fdp, "end", &psize);

	test = malloc(sizeof(char*) * 5);
	test[0] = ft_strdup("cat"); 
	test[1] = ft_strdup("$_"); 
	test[2] = NULL;
	execve("/usr/bin/cat", test, envp);

	int		pid;
	test = malloc(sizeof(char*) * 5);
	test[0] = ft_strdup("cat"); 
	test[2] = NULL;
	int savein;
	savein = dup2(fdp[0], 0);
	pid = fork();
	if (pid == 0)
		execve("/usr/bin/cat", test, envp);
	dup2(savein, 0);


	close(fdp[0]);
	close(fdp[1]);

	char	**test;
	char	*arg;

	arg = malloc(sizeof(char) * 15);
	arg[0] = '"';
	arg[1] = '$';
	arg[2] = 'E';
	arg[3] = 'N';
	arg[4] = 'D';
	arg[5] = '"';
	arg[6] = '\0';

	*/
	return (0);
}
