/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 18:07:12 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/13 18:07:57 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_cmp(const char *rl, const char *match)
{
	while (*rl && *match)
	{
		if (*rl != *match)
			return (1);
		rl++;
		match++;
	}
	if (*rl != *match)
		return (1);
	return (0);
}

int	write_in_fd(const char *rl, int fd)
{
	char	*cont;
	int		i;

	i = 0;
	cont = ft_strdup(rl);
	cont = change_content(cont);
	if (!cont)
		return (-1);
	while (cont[i])
	{
		write(fd, (cont + i), 1);
		i++;
	}
	write(fd, "\n", 1);
	free(cont);
	return (0);
}

int	create_double(int pfd[2], const char *match)
{
	char	*rl;

	rl = readline(">");
	while (str_cmp(rl, match))
	{
		if (write_in_fd(rl, pfd[1]))
			return (-1);
		rl = readline(">");
	}
	return (0);
}

int	create_heredoc(t_content *lst)
{
	t_content	*tmp;

	while (lst)
	{
		if (lst->token == 5)
		{
			tmp = lst;
			tmp = tmp->next;
			if (!tmp)
				return (-1);
			if (tmp->token != 1)
				return (-1);
			pipe(lst->pfd);
			if (create_double(lst->pfd, lst->next->content))
				return (33);
			close(lst->pfd[1]);
		}
		lst = lst->next;
	}
	return (0);
}
