/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:11:17 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/19 16:20:17 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_if_redirection(char *cont, t_env *lenv)
{
	char *tmp;

	tmp = ft_strdup(cont);
	tmp = change_content(tmp, lenv); 
	if (!tmp)
		return (NULL);
	if (*tmp)
	{
		free(tmp);
		return (change_content(cont, lenv));
	}
	free(tmp);
	return (cont);
}

void	pass_simple_quotes(char **cont, char *new, int *i)
{
	new[(*i)++] = *(*cont)++;
	while (**cont && **cont != '\'')
		new[(*i)++] = *(*cont)++;
	new[(*i)++] = *(*cont)++;
}

char	*change_content(char *cont, t_env *lenv)
{
	int		dq;
	char	*new;
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	dq = 1;
	tmp = cont;
	len = ft_strlen(tmp) + 1;
	new = malloc(sizeof(char) * len);
	while (*tmp)
	{
		if (*tmp == '"')
			dq = -dq;
		if (*tmp == '\'' && dq == 1)
			pass_simple_quotes(&tmp, new, &i);
		else if (*tmp == '$' && *(tmp + 1) && *(tmp + 1) == '?')
			new = dol_is_interrog(new, &tmp, &i, &len);
		else if (*tmp == '$' && *(tmp + 1) && (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '_'))
			new = dol_is_env(new, &tmp, &i, &len, lenv);
		else
			new[i++] = *tmp++;
		if (!new)
			return (NULL);
	}
	free(cont);
	new[i] = '\0';
	return (new);
}

int		replace_env(t_content *lst, t_env *lenv)
{
	t_content *before;

	before = lst;
	lst->content = change_content(lst->content, lenv);
	if (!lst->content)
		return (-1);
	lst = lst->next;
	while (lst)
	{
		if (before->token == 1 || before->token == 6)
		{
			lst->content = change_content(lst->content, lenv);
			if (!*lst->content)
				lst->token = 999;
		}
		else if (before->token == 2 || before->token == 3 || before->token == 4)
			lst->content = check_if_redirection(lst->content, lenv);
		if (!lst->content)
			return (-1);
		lst = lst->next;
		before = before->next;
	}
	return (0);
}
