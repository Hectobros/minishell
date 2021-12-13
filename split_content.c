/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:55:24 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/13 12:17:11 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*char_is_meta(const char *p)
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

int	split_all_content(const char *line, t_content **lst)
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
