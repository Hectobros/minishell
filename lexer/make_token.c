/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:14:29 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 09:19:36 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_useless_env(t_content *lst)
{
	t_content	*tmp;

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

void	file_var_inquotes(t_content *lst)
{
	t_content	*bef;
	char		*tmp;

	bef = lst;
	lst = lst->next;
	while (lst)
	{
		tmp = lst->content;
		if ((bef->token == 2 || bef->token == 3 || bef->token == 4)
			&& *tmp == '$' && *(tmp + 1)
			&& (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '_'))
			lst->token = 666;
		bef = bef->next;
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

int	only_whitespace(char *rl)
{
	while (*rl && ((*rl > 8 && *rl < 14) || *rl == ' '))
		rl++;
	if (*rl)
		return (0);
	return (1);
}

int	make_token(char *rl, t_content **lst, t_env *lenv)
{
	if (ft_strlen(rl) == 0 || only_whitespace(rl))
		return (0);
	if (check_open_quotes(rl))
	{
		printf("minishell: quotes not closed\n");
		return (0);
	}
	if (split_all_content(rl, lst))
		exit(33);
	give_token(*lst);
	if (*lst)
		if (replace_env(*lst, lenv))
			exit(33);
	del_useless_env(*lst);
	file_var_inquotes(*lst);
	remove_quotes(*lst);
	return (0);
}
