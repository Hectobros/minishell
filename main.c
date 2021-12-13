/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/13 13:05:59 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_content_lst(t_content *lst)
{
	t_content	*tmp;

	while (lst)
	{
		tmp = lst;
		free(lst->content);
		lst = lst->next;
		free(tmp);
	}
	return (0);
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

void	give_token(t_content *lst)
{
	char	*tmp;

	while (lst)
	{
		tmp = lst->content;
		if (tmp[0] == '|')
			lst->token = 6;
		else if (tmp[0] == '>' && tmp[1] == '\0')
			lst->token = 2;
		else if (tmp[0] == '>' && tmp[1] == '>')
			lst->token = 3;
		else if (tmp[0] == '<' && tmp[1] == '\0')
			lst->token = 4;
		else if (tmp[0] == '<' && tmp[1] == '<')
			lst->token = 5;
		else
			lst->token = 1;
		lst = lst->next;
	}
}





















char 	*dol_is_interrog(char *new, char **cont, int *i, int *len)
{
	(void)i;
	(void)len;
	(void)new;
	(void)cont;

	new[(*i)++] = *(*cont)++;
	return (new);
}



char	*re_alloc(char *buff, int hl, int limit)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * hl);
	if (!new)
		return (NULL);
	while (i < limit)
	{
		new[i] = buff[i];
		i++;
	}
	free(buff);
	return (new);
}

char	*get_env_name(char *cont)
{
	const char	*tmp;
	char		*dest;
	int			size;
	int			i;

	i = 0;
	size = 0;
	tmp = cont;
	while (*tmp && (ft_isalnum(*tmp) || *tmp == '_'))
	{
		size++;
		tmp++;
	}
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (*cont && (ft_isalnum(*cont) || *cont == '_'))
	{
		dest[i] = *cont;
		cont++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


void	cut_env_name(char **cont)
{
	(*cont)++;
	while (**cont && (ft_isalnum(**cont) || **cont == '_'))
		(*cont)++;
}
char	*dol_is_env(char *new, char **cont, int *i, int *len)
{
	char	*envname;
	char	*envdata;

	envname = get_env_name(*cont + 1);
	if (!envname)
		return (NULL);
	envdata = getenv(envname);
	free(envname);
	if (envdata && *envdata != '\0')
	{
		*len = *len + ft_strlen(envdata);
		new = re_alloc(new, *len, *i);
		if (!new)
			return (NULL);
		while (*envdata)
			new[(*i)++] = *envdata++;
	}
	cut_env_name(cont);
	return (new);
}


void	pass_simple_quotes(char **cont, char *new, int *i)
{
	new[(*i)++] = *(*cont)++;
	while (**cont && **cont != '\'')
		new[(*i)++] = *(*cont)++;
	new[(*i)++] = *(*cont)++;
}
char	*change_content(char *cont)
{
	char	*new;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(cont) + 1;
	new = malloc(sizeof(char) * len);
	while (*cont)
	{
		if (*cont == '\'')
			pass_simple_quotes(&cont, new, &i);
		if (*cont == '$' && *(cont + 1) && *(cont + 1) == '?')
			new = dol_is_interrog(new, &cont, &i, &len);
		else if (*cont == '$' && *(cont + 1) && (ft_isalnum(*(cont + 1)) || *(cont + 1) == '_'))
			new = dol_is_env(new, &cont, &i, &len);
		else
			new[i++] = *cont++;
		if (!new)
			return (NULL);
	}
	new[i] = '\0';
	return (new);
}

char	*check_if_redirection(char *cont)
{
	char *tmp;

	tmp = ft_strdup(cont);
	tmp = change_content(tmp); 
	if (!tmp)
		return (NULL);
	if (*tmp)
	{
		free(tmp);
		return (change_content(cont));
	}
	free(tmp);
	return (cont);
}

int		replace_env(t_content *lst)
{
	t_content *before;

	before = lst;
	lst->content = change_content(lst->content);
	if (!lst->content)
		return (-1);
	lst = lst->next;
	while (lst)
	{
		if (before->token == 1 || before->token == 6)
		{
			lst->content = change_content(lst->content);
			if (!*lst->content)
				lst->token = 999;
		}
		else if (before->token == 2 || before->token == 3 || before->token == 4)
			lst->content = check_if_redirection(lst->content);
		if (!lst->content)
			return (-1);
		lst = lst->next;
		before = before->next;
	}
	return (0);
}

void	del_useless_env(t_content *lst)
{
	t_content *tmp;

	while (lst)
	{
		tmp = lst->next;
		if (tmp && tmp->token == 999)
		{
			lst->next = tmp->next;
			free(tmp->content);
			free(tmp);
		}
		lst = lst->next;
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
		printf("child:%d\n", execve("/usr/bin/cat", test, NULL));
	}
	waitpid(0, NULL, 0);

}

void	read_heredoc(t_content *lst)
{
	while (lst)
	{
		if (lst->token == 5)
			test_inside_fd(lst->pfd);
		lst = lst->next;
	}
}

void	close_heredoc_pipes(t_content *lst)
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





int	str_cmp(const char *line, const char *match)
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

int	write_in_fd(const char *line, int fd)
{
	char	*cont;
	int		i;

	i = 0;
	cont = ft_strdup(line);
	cont = change_content(cont);
	if (!cont)
		return (-1);
	while (cont[i])
	{
		write(fd, (cont + i), 1);
		i++;
	}
	write(fd, "\n", 1);
	free(cont);
	return (0);
}

int	create_double(int pfd[2], const char *match)
{
	char	*line;

	line = readline(">");
	while (str_cmp(line, match))
	{
		if (write_in_fd(line, pfd[1]))
			return (-1);
		line = readline(">");
	}
	return (0);
}

int	create_heredoc(t_content *lst)
{
	t_content	*tmp;

	while (lst)
	{
		if (lst->token == 5)
		{
			tmp = lst;
			tmp = tmp->next;
			if (!tmp)
				return (-1);
			if (tmp->token != 1)
				return (-1);
			pipe(lst->pfd);
			if (create_double(lst->pfd, lst->next->content))
				return (33);
			close(lst->pfd[1]);
		}
		lst = lst->next;
	}
	return (0);
}


int	make_token(const char *rl, t_content **lst)
{
	//	char	*line;

	if (check_open_quotes(rl))
		return (-1);
	//	line = replace_env(rl);
	//	if (!line)
	//		return (33);
	if (split_all_content(rl, lst))
		return (33);
	give_token(*lst);
	if (*lst)
		if (replace_env(*lst))
			return (33);
	del_useless_env(*lst);
	remove_quotes(*lst);



	if (create_heredoc(*lst))
		return (33);
	//traduction when writting inside pipe;
	read_heredoc(*lst);//temporaire
	close_heredoc_pipes(*lst);// pour NIELS

	print_lst(*lst);
	//	free(line);
	return (0);
}

int	main(void)
{
	t_content	*lst;
	int			exit;
	char		*line;
	const char	*prompt;

	exit = 1;
	prompt = "minishell$ ";
	while (exit)
	{
		lst = NULL;
		line = readline(prompt);
		if (ft_strlen(line) != 0)
			add_history (line);
		if (make_token(line, &lst))
		{
			printf("Error\n");
			return (1);
		}
		free_content_lst(lst);
	}
	return (0);
}
