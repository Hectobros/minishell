/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:45:54 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 08:42:08 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		ltmp = last_env(*lst);
		ltmp->next = lnew;
	}
	else
		*lst = lnew;
}

char	*get_env_value(const char *env)
{
	char	*value;
	int		i;

	i = 0;
	while (*env && *env != '=')
		env++;
	if (*env)
		env++;
	value = malloc(sizeof(char) * (1 + ft_strlen(env)));
	if (!value)
		return (NULL);
	while (*env)
		value[i++] = *env++;
	value[i] = '\0';
	return (value);
}

int	create_env_lst(t_env **lst, char **env)
{
	int		i;
	char	*name;
	char	*value;

	(void)lst;
	(void)name;
	i = 0;
	while (env[i])
	{
		name = get_env_name(env[i]);
		value = get_env_value(env[i]);
		if (!name || !value)
			return (33);
		add_back_env(lst, new_env(name, value));
		i++;
	}
	return (0);
}
