/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/10 21:18:57 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*   if > > ???
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
 */
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



char	*get_env_name(const char *cont)
{
	const char	*tmp;
	char	*dest;
	int		size;
	int		i;

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
	while (*p >= '0' && *p++ <= '9')
		size++;
	*len = *len + 4 + size;
	dest = re_alloc(dest, *len, *i);
	str_addback(dest, i, "bash", 4);
	(*rl)++;
	while (**rl >= '0' && **rl <= '9')
	{
		dest[(*i)++] = **rl;
		(*rl)++;
	}
	return (dest);
}

char	*dol_is_env(int *i, int *len, char *dest, const char **rl)
{
	char	*envname;
	char	*envdata;

	envname = get_env_name(*rl);
	if (!envname)
		return (NULL);
	envdata = getenv(envname);
	if (envdata)
	{
		*len = *len + ft_strlen(envdata);
		dest = re_alloc(dest, *len, *i);
		while (*envdata)
			dest[(*i)++] = *envdata++;
	}
	(*rl)++;
	while (**rl && (ft_isalnum(**rl) || **rl == '_'))
		(*rl)++;
	free(envname);
	return (dest);
}

char	*replace_dol(int *i, int *len, char *dest, const char **rl)//NEED TO ADD $$
{// ADD : id < or > before $FAIL   --->   $FAIL persiste
	(*rl)++;
	if ((**rl >= '1' && **rl <= '9'))
		(*rl)++;
	else if (**rl == '0')
		dest = dol_is_bash(i, len, dest, rl);
	else
		dest = dol_is_env(i, len, dest, rl);
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
		else if (*rl && need_to_change(rl))
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

int	make_token(const char *rl, t_content **lst)
{
	char	*line;


	if (check_open_quotes(rl))
		return (-1);
	line = replace_env(rl);
	if (!line)
		return (-1);

	//	printf("%s\n", line);

	//	(void)lst;

	if (split_all_content(line, lst))
		return (-1);
	give_token(*lst);
	remove_quotes(*lst);

	print_lst(*lst);

	//	if (regroup_redir(*lst))// !!! fail si espace entre > > !!!
	//		return (-1);
	//	delete_empty_content(*lst); //doit conserver infos !

	free(line);
	return (0);
}

int	main(void)
{
	t_content	*lst;
	int		exit;
	char	*line;
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
