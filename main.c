/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/09 11:46:34 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dup_until_space(const char *src)
{
	const char	*tmp;
	int		size;
	char	*dest;
	int		i;

	i = 0;
	size = 0;
	tmp = src;
	while (*tmp && *tmp++ != ' ')
		++size;
	size = size + 1;
	dest = malloc(sizeof(char) * size);
	if (dest == NULL)
		return (NULL);
	while (src[i] && src[i] != ' ')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*dup_until_quotes(const char *src, char c)
{
	const char	*tmp;
	int		size;
	char	*dest;
	int		i;

	i = 0;
	size = 1;
	tmp = src;
	while (*tmp && *tmp++ != c)
		++size;
	size = size + 2;
	dest = malloc(sizeof(char) * size);
	if (dest == NULL)
		return (NULL);
	dest[i++] = c;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i++] = c;
	dest[i] = '\0';
	return (dest);
}

int	split_all_content(char *line, t_content **lst)
{
	char		*content;

	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line == '"')
		{
			content = dup_until_quotes(line, '"');
			add_back(lst, new_lst(content));
			line++;
			while (*line && *line != '"')
				line++;
			line++;
		}
		else if (*line == '\'')
		{
			content = dup_until_quotes(line, '\'');
			add_back(lst, new_lst(content));
			line++;
			while (*line && *line != '\'')
				line++;
			line++;
		}
		else if (*line)
		{
			content = dup_until_space(line);
			add_back(lst, new_lst(content));
			while (*line && *line != ' ')
				line++;
		}
	}

	return (0);
}

int	lexer_maker(char *line, t_content **lst)
{
	if (check_open_quotes(line))
		return (1);
	if (split_all_content(line, lst))
		return (1);

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
	lst = NULL;
	while (exit)
	{
		line = readline(prompt);
		if (ft_strlen(line) != 0)
			add_history (line);
		if (lexer_maker(line, &lst))
			printf("Error\n");
		while (lst)
		{
			printf("content:%s\n", lst->content);
			lst = lst->next;
		}
	}
	return (0);
}
