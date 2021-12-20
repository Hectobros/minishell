/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 09:49:37 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 10:27:05 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_all(t_mini *l)
{
	int	status;

	while (l && l->cmd)
	{
		waitpid(l->pid, &status, 0);
		if (WIFEXITED(status))
			g_globa.herve = (WEXITSTATUS(status) % 256);
		l = l->next;
	}
}

int	dad_is_running(t_mini *l, t_env *lenv)
{
	int	ret;

	ret = 0;
	if (!l->cmd)
		ret = 0;
	else if (str_comp(l->cmd[0], "cd"))
		ret = cd42(l->cmd, lenv);
	else if (str_comp(l->cmd[0], "export"))
		ret = export42(l->cmd, &lenv);
	else if (str_comp(l->cmd[0], "unset"))
		ret = unset42(l->cmd, &lenv);
	else if (str_comp(l->cmd[0], "exit"))
		ret = exit42(l->cmd);
	return (ret);
}

int	is_parent(t_mini *l)
{
	if (!l->cmd)
		return (0);
	else if (str_comp(l->cmd[0], "cd"))
		return (1);
	else if (str_comp(l->cmd[0], "export"))
		return (1);
	else if (str_comp(l->cmd[0], "unset"))
		return (1);
	else if (str_comp(l->cmd[0], "exit"))
		return (1);
	return (0);
}
