/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:42:31 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 09:47:31 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_mini *l)
{
	if (!l->cmd)
		return (0);
	else if (str_comp(l->cmd[0], "echo"))
		return (1);
	else if (str_comp(l->cmd[0], "cd"))
		return (1);
	else if (str_comp(l->cmd[0], "pwd"))
		return (1);
	else if (str_comp(l->cmd[0], "env"))
		return (1);
	else if (str_comp(l->cmd[0], "export"))
		return (1);
	else if (str_comp(l->cmd[0], "unset"))
		return (1);
	else if (str_comp(l->cmd[0], "exit"))
		return (1);
	return (0);
}

int	len_mini(t_mini *com)
{
	int	len;

	len = 0;
	while (com)
	{
		len++;
		com = com->next;
	}
	return (len);
}

void	add_prev_mini(t_mini *com)
{
	t_mini	*tmp;

	tmp = NULL;
	while (com)
	{
		com->prev = tmp;
		tmp = com;
		com = com->next;
	}
}

int	is_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i + 1])
		i++;
	while (i > 0 && str[i] == ' ')
		i--;
	if (i > 0 && str[i] == '|')
		return (1);
	return (0);
}

char	*pipe_at_end(char *rl)
{
	char	*rl2;
	char	*tmp;

	if (!is_pipe(rl))
		return (rl);
	rl2 = readline(">");
	if (rl2 == NULL)
		return (rl);
	while (*rl2 == '\0' || is_pipe(rl2))
	{
		tmp = rl;
		rl = ft_strjoin(rl, rl2);
		if (!rl)
			return (NULL);
		free(tmp);
		free(rl2);
		rl2 = readline(">");
		if (rl2 == NULL)
			return (rl);
	}
	tmp = rl;
	rl = ft_strjoin(rl, rl2);
	free(tmp);
	free(rl2);
	return (rl);
}
