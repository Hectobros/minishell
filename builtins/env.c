/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:14:02 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 08:32:25 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env42(char **cmd, t_env *lst)
{
	if (cmd[1])
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		return (127);
	}
	while (lst)
	{
		printf("%s=%s\n", lst->name, lst->value);
		lst = lst->next;
	}
	return (0);
}

void	delete_first(t_env **lst)
{
	t_env	*tmp;

	tmp = (*lst);
	*lst = (*lst)->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
}

void	delete_env(t_env *lp, char **cmd, int i)
{
	t_env	*tmp;

	while (lp)
	{
		tmp = lp->next;
		if (tmp && str_comp(tmp->name, cmd[i]))
		{
			lp->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
		}
		lp = lp->next;
	}
}

int	unset_is_valid(char *str)
{
	if (*str > '0' && *str < '9')
		return (1);
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	if (*str)
		return (1);
	return (0);
}

int	unset42(char **cmd, t_env **lst)
{
	int	ret;
	int	i;

	i = 1;
	ret = 0;
	while (cmd[i])
	{
		if (unset_is_valid(cmd[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
			ret = 1;
		}
		else
		{
			if (str_comp((*lst)->name, cmd[i]))
				delete_first(lst);
			else
				delete_env(*lst, cmd, i);
		}
		i++;
	}
	return (ret);
}
