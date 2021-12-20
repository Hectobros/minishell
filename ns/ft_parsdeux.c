/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsdeux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:38:43 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 10:38:44 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstok(t_content *l)
{
	int			previous;
	t_content	*lst;

	lst = l;
	previous = 0;
	while (lst != NULL)
	{
		if (previous == 0 && lst->token == 6)
			return (16);
		if ((previous != 0 && previous != 1 && previous != 666)
			&& (!(lst->token == 1 || lst->token == 666))
			&& (!(previous == 6 && lst->token > 2 && lst->token < 6)))
			return (10 + lst->token);
		previous = lst->token;
		lst = lst->next;
	}
	if (previous != 1 && previous != 0 && previous != 666)
		return (10);
	return (0);
}

int	ft_nbpipe(t_content *l)
{
	t_content	*lst;
	int			nbpipe;

	lst = l;
	nbpipe = 1;
	while (lst)
	{
		if (lst->token == 6)
			nbpipe++;
		lst = lst->next;
	}
	return (nbpipe);
}

char	**ft_tabdupgrand(char **tab, char *str)
{
	int		x;
	int		y;
	char	**temp;

	x = 0;
	y = 0;
	while (tab[x])
		x++;
	temp = malloc(sizeof(char *) * (x + 2));
	while (y < x)
	{
		temp[y] = tab[y];
		y++;
	}
	free(tab);
	temp[y] = str;
	temp[y + 1] = NULL;
	return (temp);
}

void	ft_addcom(char *content, t_mini *commande)
{
	if (commande->cmd == NULL)
	{
		commande->cmd = malloc(sizeof(char *) * 2);
		commande->cmd[0] = ft_strdup(content);
		commande->cmd[1] = NULL;
	}
	else
		commande->cmd = ft_tabdupgrand(commande->cmd, ft_strdup(content));
}

int	ft_isdir(t_content *l, t_mini *com)
{
	int			x;
	struct stat	path_stat;

	x = 0;
	stat(l->content, &path_stat);
	x = S_ISDIR(path_stat.st_mode);
	if (x == 0)
		return (0);
	else
	{
		com->fdout = -3;
		if (com->crashword == NULL)
			com->crashword = ft_strdupn(l->content);
		return (-1);
	}
}
