/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openner.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:38:50 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 10:38:51 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open(t_content *l, t_mini *com, int token)
{
	int	fd;

	fd = 0;
	if (token == 2 || token == 3)
	{
		if (com->fdout >= 0)
			close(com->fdout);
		if (ft_isdir(l->next, com) != 0)
			return (-3);
		if (ft_ambigous(l->next, com, 1) != 0)
			return (-2);
		ft_openone(l, com, token);
		fd = com->fdout;
	}
	else if (token == 4 || token == 5)
	{
		if (com->fdin != -500)
			close(com->fdin);
		if (ft_ambigous(l->next, com, 0) != 0)
			return (-2);
		ft_opendeux(l, com, token, fd);
		fd = com->fdin;
	}
	return (fd);
}

int	ft_openone(t_content *l, t_mini *com, int token)
{
	if (token == 2)
	{
		com->fdout = open(l->next->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (com->fdout == -1)
		{
			if (com->crashword)
				free(com->crashword);
			com->crashword = ft_strdup(l->next->content);
		}
	}
	else
	{
		com->fdout = open(l->next->content,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (com->fdout == -1)
		{
			if (com->crashword)
				free(com->crashword);
			com->crashword = ft_strdup(l->next->content);
		}
	}
	return (0);
}

void	ft_opendeux(t_content *l, t_mini *com, int token, int fd)
{
	if (token == 4)
	{
		com->fdin = open(l->next->content, O_RDONLY);
		if (com->fdin == -1)
		{
			fd = access(l->next->content, F_OK);
			if (!fd)
				com->fdin = -1;
			else
				com->fdin = -4;
			if (com->crashword)
				free(com->crashword);
			com->crashword = ft_strdup(l->next->content);
		}
	}
	else if (token == 5)
		com->fdin = l->pfd[0];
}
