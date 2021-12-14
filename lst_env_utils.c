/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:45:54 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/14 17:37:41 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *name, char *value)
{
	t_env	*lnew;

	lnew = malloc(sizeof(t_env));
	if (lnew == NULL)
		return (NULL);
	lnew->name = name;
	lnew->value = value;
	lnew->next = NULL;
	return (lnew);
}

t_env	*last_env(t_env *lst)
{
	t_env	*lret;

	lret = NULL;
	while (lst)
	{
		lret = lst;
		lst = lst->next;
	}
	return (lret);
}

void	add_back_env(t_env **lst, t_env *lnew)
{
	t_env	*ltmp;

	if (*lst)
	{
		ltmp = last_ptr(*lst);
		ltmp->next = lnew;
	}
	else
		*lst = lnew;
}

int	create_env_lst(t_env **lst, char **env)
{


}

int	main(int ac, char **av, char **env)
{
	t_env	*env;

	create_env_lst(&lst, env);


	return (0);
}
