/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/10 12:54:56 by jvermeer         ###   ########.fr       */
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
		printf("content:%s\n", lst->content);
		lst = lst->next;
	}
}

int		remove_quote(char *str, char c)
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
	int i;

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
	char *tmp;

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

int	is_metachar(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '\n' || c == ' ' || c == '\t')
		return (1);
	return (0);
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
			while(src[i] != c)
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
			content = malloc(sizeof(char) * 2);
			if (!content)
				return (-1);
			content[0] = *line;
			content[1] = '\0';
			add_back(lst, new_lst(content));
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

int	regroup_redir(t_content *lst)
{
	t_content *tmp;
	char	*new;
	char	redir;

	while (lst)
	{
		if (*lst->content == '>' || *lst->content == '<')
		{
			redir = *lst->content;
			tmp = lst;
			tmp = tmp->next;
			if (tmp && *tmp->content == redir)
			{
				new = malloc(sizeof(char) * 3);
				if (!new)
					return (-1);
				new[0] = redir;
				new[1] = redir;
				new[2] = '\0';
				free(lst->content);
				lst->content = new;
				lst->next = tmp->next;
				free(tmp->content);
				free(tmp);
			}
		}
		lst = lst->next;
	}
	return (0);
}

void	delete_empty_content(t_content *lst)
{
	t_content *tmp;
	t_content *beg;

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

int	make_token(char *line, t_content **lst)
{
	if (check_open_quotes(line))
		return (-1);
	if (split_all_content(line, lst))
		return (-1);
	if (regroup_redir(*lst))
		return (-1);
	give_token(*lst);
	print_lst(*lst);

	//PLACE TOKEN

	//REPLACE PATHH

	//		remove_quotes(*lst);
	//	delete_empty_content(*lst);
	//		printf("///////////////////////////////remove quotes\n");
	return (0);
}

int	main(void)
{
	t_content	*lst;
	int		exit;
	char	*line;
	const char	*prompt;

	prompt = "minishell$ ";

	exit = 1;
	while (exit)
	{
		lst = NULL;
		line = readline(prompt);

		if (ft_strlen(line) != 0)
			add_history (line);
		if (make_token(line, &lst))
			printf("Error\n");

		free_content_lst(lst);
	}
	return (0);
}
