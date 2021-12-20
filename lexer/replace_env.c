/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:11:17 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 09:15:26 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_if_redirection(char *cont, t_env *lenv)
{
	char	*tmp;

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

void	pass_simple_quotes(t_utils *u, char **cont)
{
	u->dest[u->i++] = *(*cont)++;
	while (**cont && **cont != '\'')
		u->dest[u->i++] = *(*cont)++;
	u->dest[u->i++] = *(*cont)++;
}

char	*change_content(char *cont, t_env *lenv)
{
	t_utils	u;
	char	*tmp;

	u.i = 0;
	u.dq = 1;
	tmp = cont;
	u.len = ft_strlen(tmp) + 1;
	u.dest = malloc(sizeof(char) * u.len);
	while (*tmp)
	{
		if (*tmp == '"')
			u.dq = -u.dq;
		if (*tmp == '\'' && u.dq == 1)
			pass_simple_quotes(&u, &tmp);
		else if (*tmp == '$' && *(tmp + 1) && *(tmp + 1) == '?')
			u.dest = dol_is_interrog(&u, &tmp);
		else if (*tmp == '$' && *(tmp + 1)
			&& (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '_'))
			u.dest = dol_is_env(&u, &tmp, lenv);
		else
			u.dest[u.i++] = *tmp++;
	}
	u.dest[u.i] = '\0';
	free(cont);
	return (u.dest);
}

int	replace_env(t_content *lst, t_env *lenv)
{
	t_content	*before;

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
