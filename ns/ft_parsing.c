/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:38:31 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 10:38:33 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ambigous(t_content *l, t_mini *com, int i)
{
	if (l->token == 666)
	{
		if (i == 0)
			com->fdin = -2;
		if (i == 1)
			com->fdout = -2;
		if (com->crashword)
			free(com->crashword);
		com->crashword = ft_strdupn(l->content);
		return (-1);
	}
	else
		return (0);
}

void	ft_createcom(t_mini *com, t_content *l)
{
	int			fd;
	t_content	*lst;
	t_mini		*lstcom;

	fd = 0;
	lst = l;
	lstcom = com;
	while (lst)
	{
		if (lst->token >= 2 && lst->token <= 5 && fd != -766)
		{
			fd = ft_open(lst, lstcom, lst->token);
			if (fd == -1 || fd == -2 || fd == -3 || fd == -4)
				fd = -766;
			lst = lst->next;
		}
		else if (lst->token == 1 && fd != -766)
			ft_addcom(lst->content, lstcom);
		else if (lst->token == 6)
		{
			fd = 0;
			lstcom = lstcom->next;
		}
		lst = lst->next;
	}
}

t_mini	*ft_createliste(int x)
{
	t_mini	*start;
	int		y;

	y = 0;
	start = ft_lstnewm(y);
	y++;
	while (y < x)
	{
		ft_lstadd_backm(&start, ft_lstnewm(y));
		y++;
	}
	return (start);
}

int	ft_errorsyntax(int x, t_content *l, t_env *lenv)
{
	if (x == 0)
		return (0);
	if (x == 10)
	{
		create_heredoc(l, lenv);
		return (write(1,
				"minishell: syntax error near unexpected token `newline'\n"
				, 56));
	}
	create_heredoc(l, lenv);
	ft_errord(x);
	return (1);
}

t_mini	*ft_buildpipe(t_content *l, t_env *lenv)
{
	t_mini	*lcom;

	lcom = NULL;
	if (l == NULL)
		return (NULL);
	if (ft_errorsyntax(ft_lstok(l), l, lenv) != 0)
	{
		return (NULL);
	}
	create_heredoc(l, lenv);
	lcom = ft_createliste(ft_nbpipe(l));
	ft_createcom(lcom, l);
	return (lcom);
}
