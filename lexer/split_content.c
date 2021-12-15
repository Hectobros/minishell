/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:55:24 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/15 11:54:18 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_metachar(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '\n' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	dup_non_meta(char *src, char **content)
{
	int		size;
	int		i;
	char	c;

	i = 0;
	size = ft_strlen(src);
	*content = malloc(sizeof(char) * (size + 1));
	if (!*content)
		return (0);
	while (*src && !is_metachar(*src))
	{
		if (*src == '\'' || *src == '"')
		{
			c = *src;
			content[0][i++] = *src++;
			while (*src != c)
				content[0][i++] = *src++;
		}
		content[0][i++] = *src++;
	}
	content[0][i] = '\0';
	return (i);
}

char	*char_is_meta(char **rl)
{
	char	*content;

	if ((**rl == '>' && *(*rl + 1) == '>')
		|| (**rl == '<' && *(*rl + 1) == '<'))
	{
		content = malloc(sizeof(char) * 3);
		if (!content)
			return (NULL);
		content[0] = *(*rl)++;
		content[1] = *(*rl)++;
		content[2] = '\0';
		return (content);
	}
	else
	{
		content = malloc(sizeof(char) * 2);
		if (!content)
			return (NULL);
		content[0] = *(*rl)++;
		content[1] = '\0';
		return (content);
	}
}

int	split_all_content(char *rl, t_content **lst)
{
	char	*content;
	int		add;

	while (*rl)
	{
		if (*rl == ' ' || *rl == '\t' || *rl == '\n')
			rl++;
		else if (is_metachar(*rl))
		{
			content = char_is_meta(&rl);
			if (!content)
				return (-1);
			add_back(lst, new_lst(content));
		}
		else
		{
			add = dup_non_meta(rl, &content);
			if (!content)
				return (-1);
			add_back(lst, new_lst(content));
			rl = rl + add;
		}
	}
	return (0);
}
