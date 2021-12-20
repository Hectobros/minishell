/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:38:58 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 10:39:00 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_errord(int x)
{
	if (x == 12)
		return (write(1,
				"minishell: syntax error near unexpected token `>'\n", 50));
	if (x == 13)
		return (write(1,
				"minishell: syntax error near unexpected token `>>'\n", 51));
	if (x == 14)
		return (write(1,
				"minishell: syntax error near unexpected token `<'\n", 50));
	if (x == 15)
		return (write(1,
				"minishell: syntax error near unexpected token `<<'\n", 51));
	if (x == 16)
		return (write(1,
				"minishell: syntax error near unexpected token `|'\n", 50));
	return (0);
}

void	ft_freetab(char **content)
{
	int	x;

	x = 0;
	if (content == NULL)
		return ;
	while (content[x])
	{
		free(content[x]);
		x++;
	}
	free(content);
}

int	ft_destroy(t_mini *lcom)
{
	t_mini	*temp;

	while (lcom)
	{
		if (lcom->fdin > 0)
			close(lcom->fdin);
		if (lcom->fdout > 0)
			close(lcom->fdout);
		if (lcom->crashword)
			free(lcom->crashword);
		if (lcom->cmd)
			ft_freetab(lcom->cmd);
		temp = lcom;
		lcom = lcom->next;
		free(temp);
	}
	return (1);
}

void	ft_printab(char **tab)
{
	int	x;

	x = 0;
	while (tab[x] != NULL)
	{
		printf("%s ,", tab[x]);
		x++;
	}
	printf("\n");
}

int	ft_printcomm(t_mini *com)
{
	while (com)
	{
		printf("-----COMMANDE N°%d-------\n", com->content);
		if (com->cmd)
			ft_printab(com->cmd);
		printf("FDIN:%d\n", com->fdin);
		printf("FDOUT:%d\n", com->fdout);
		if (com->crashword != NULL)
			printf("CRASHWORD: %s\n", com->crashword);
		printf("-----FIN DE COMMANDE------\n");
		com = com->next;
	}
	return (0);
}
