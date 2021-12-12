/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/12 19:28:46 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '\n' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

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

int	remove_quote(char *str, char c)
{
	char	*tmp;

	while (*str)
	{
		if (*str == c)
		{
			tmp = str;
			tmp++;
			while (*tmp)
				*str++ = *tmp++;
			*str = '\0';
			return (0);
		}
		str++;
	}
	return (0);
}

int	remove_both_quotes(char *tmp, char c)
{
	int	i;

	i = 0;
	remove_quote(tmp, c);
	while (*tmp != c)
	{
		i++;
		tmp++;
	}
	remove_quote(tmp, c);
	return (i);
}

void	remove_quotes(t_content *lst)
{
	char	*tmp;

	while (lst)
	{
		tmp = lst->content;
		while (*tmp)
		{
			if (*tmp == '"' || *tmp == '\'')
				tmp = tmp + remove_both_quotes(tmp, *tmp);
			else
				tmp++;
		}
		lst = lst->next;
	}
}

int	dup_non_meta(const char *src, char **dest)
{
	int		size;
	int		i;
	char	c;

	i = 0;
	size = ft_strlen(src);
	dest[0] = malloc(sizeof(char) * (size + 1));
	if (!dest[0])
		return (0);
	while (src[i] && !is_metachar(src[i]))
	{
		if (src[i] == '\'' || src[i] == '"')
		{
			c = src[i];
			dest[0][i] = src[i];
			i++;
			while (src[i] != c)
			{
				dest[0][i] = src[i];
				i++;
			}
		}
		dest[0][i] = src[i];
		i++;
	}
	dest[0][i] = '\0';
	return (i);
}

char	*char_is_meta(char *p)
{
	char	c;
	char	*content;

	if ((*p == '>' && *(p + 1) == '>') || (*p == '<' && *(p + 1) == '<'))
	{
		c = *p;
		content = malloc(sizeof(char) * 3);
		if (!content)
			return (NULL);
		content[0] = c;
		content[1] = c;
		content[2] = '\0';
		return (content);
	}
	else
	{
		c = *p;
		content = malloc(sizeof(char) * 2);
		if (!content)
			return (NULL);
		content[0] = c;
		content[1] = '\0';
		return (content);
	}
}

int	split_all_content(char *line, t_content **lst)
{
	char	*content;
	int		add;

	while (*line)
	{
		if (*line == ' ' || *line == '\t' || *line == '\n')
			line++;
		else if (is_metachar(*line))
		{
			content = char_is_meta(line);
			if (!content)
				return (-1);
			add_back(lst, new_lst(content));
			if (ft_strlen(content) == 2)
				line++;
			line++;
		}
		else
		{
			add = dup_non_meta(line, &content);
			if (!content)
				return (-1);
			add_back(lst, new_lst(content));
			line = line + add;
		}
	}
	return (0);
}

void	delete_empty_content(t_content *lst)
{
	t_content	*tmp;
	t_content	*beg;

	beg = lst;
	while (lst)
	{
		tmp = lst;
		tmp = tmp->next;
		if (tmp && *tmp->content == '\0')
		{
			lst->next = tmp->next;
			free(tmp->content);
			free(tmp);
			lst = beg;
		}
		else
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

char	*get_env_name(const char *cont)
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

int	need_to_change(const char *p)
{
	if (*p == '$' && *(p + 1) && (ft_isalnum(*(p + 1)) || *(p + 1) == '_'))
		return (1);
	return (0);
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

void	str_addback(char *dest, int *i, const char *str, int hl)
{
	int	j;

	j = 0;
	while (j < hl)
	{
		dest[(*i)++] = *str++;
		j++;
	}
}

char	*dol_is_bash(int *i, int *len, char *dest, const char **rl)
{
	const char	*p;
	int			size;

	p = *rl;
	size = 0;
	*len = *len + 4;
	dest = re_alloc(dest, *len, *i);
	str_addback(dest, i, "bash", 4);
	(*rl)++;
	return (dest);
}

char	*dol_is_interrog(int *i, int *len, char *dest, const char **rl)
{
	(void)len;
	(void)i;
	(void)rl;
	return (dest);
}

int	is_after_redir(char *dest, int *i)
{
	int	j;

	j = *i - 1;
	while (j && dest[j] == ' ')
		j--;
	if (j >= 0 && (dest[j] == '<' || dest[j] == '>'))
	{
		dest[(*i)++] = '$';
		return (1);
	}
	return (0);
}

void	env_is_incorrect(int *i, char *dest, const char **rl)
{
	if (!is_after_redir(dest, i))
		while (**rl && (ft_isalnum(**rl) || **rl == '_'))
			(*rl)++;
	else
		while (**rl && (ft_isalnum(**rl) || **rl == '_'))
			dest[(*i)++] = *(*rl)++;
}

char	*dol_is_env(int *i, int *len, char *dest, const char **rl)
{
	char	*envname;
	char	*envdata;

	envname = get_env_name((*rl + 1));
	if (!envname)
		return (NULL);
	envdata = getenv(envname);
	free(envname);
	(*rl)++;
	if (envdata && *envdata != '\0')
	{
		*len = *len + ft_strlen(envdata);
		dest = re_alloc(dest, *len, *i);
		while (*envdata)
			dest[(*i)++] = *envdata++;
		while (**rl && (ft_isalnum(**rl) || **rl == '_'))
			(*rl)++;
	}
	else
		env_is_incorrect(i, dest, rl);
	return (dest);
}

int	is_special_dol(char c)
{
	if ((c >= '0' && c <= '9') || c == '-' || c == '#'
		|| c == '$' || c == '@' || c == '*' || c == '!')
		return (1);
	return (0);
}

char	*replace_dol(int *i, int *len, char *dest, const char **rl)
{
	const char	*p;

	p = *rl;
	p++;
	if (*p == '?')
		dest = dol_is_interrog(i, len, dest, rl);
	else if (!is_special_dol(*p))
		dest = dol_is_env(i, len, dest, rl);
	else
		dest[(*i)++] = *(*rl)++;
	return (dest);
}

char	*replace_env(const char *rl)
{
	char	*dest;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(rl) + 1;
	dest = malloc(sizeof(char) * len);
	if (!dest)
		return (NULL);
	while (*rl)
	{
		if (*rl == '\'')
		{
			dest[i++] = *rl++;
			while (*rl && *rl != '\'')
				dest[i++] = *rl++;
			dest[i++] = *rl++;
		}
		if (*rl && need_to_change(rl))
		{
			dest = replace_dol(&i, &len, dest, &rl);
			if (!dest)
				return (NULL);
		}
		else
			dest[i++] = *rl++;
	}
	dest[i] = '\0';
	return (dest);
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

void	write_in_fd(const char *line, int fd)
{
	while (*line)
	{
		write(fd, line, 1);
		line++;
	}
	write(fd, "\n", 1);
}

void	create_double(int pfd[2], const char *match)
{
	char	*line;

	line = readline(">");
	while (str_cmp(line, match))
	{
		write_in_fd(line, pfd[1]);
		line = readline(">");
	}
}

void	create_heredoc(t_content *lst)
{
	while (lst)
	{
		if (lst->token == 5)
		{
			pipe(lst->pfd);
			create_double(lst->pfd, lst->next->content);
			close(lst->pfd[1]);
		}
		lst = lst->next;
	}
}

int	check_correct_heredoc(t_content *lst)
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
		}
		lst = lst->next;
	}
	return (0);
}







void	test_inside_fd(int pfd[2])
{
	char	**test;
	int		pid;
	int		savein;

	test = malloc(sizeof(char*) * 2);

	test[0] = ft_strdup("cat"); 
	test[1] = NULL;
	savein = dup2(pfd[0], 0);
	pid = fork();
	if (pid == 0)
		printf("child:%d\n", execve("/usr/bin/cat", test, NULL));
	waitpid(0, NULL, 0);
	dup2(savein, 0);

}

void	read_heredoc(t_content *lst)
{
	while (lst)
	{
		if (lst->token == 5)
			test_inside_fd(lst->pfd);
		lst = lst->next;
	}
	printf("HERE\n");
}


int	make_token(const char *rl, t_content **lst)
{
	char	*line;

	if (check_open_quotes(rl))
		return (-1);
	line = replace_env(rl);
	if (!line)
		return (33);
	if (split_all_content(line, lst))
		return (33);
	give_token(*lst);
	remove_quotes(*lst);
//	if (check_correct_heredoc(*lst))//NEED to be mixed with create enculados
//		return (33);
//	create_heredoc(*lst);
	//traduction when writting inside pipe;

//	read_heredoc(*lst);//temporaire
//	close_heredoc_pipes(*lst);// pour NIELS
	//create function which change path into env name

	print_lst(*lst);
	free(line);
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
		//HERE
		free_content_lst(lst);
	}
	return (0);
}
