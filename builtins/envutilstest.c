/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envutilstest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:45:54 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/16 10:46:24 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_env(t_env *lst)
{
	t_env	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	return (0);
}

int	str_comp(char *name, char *unset)
{
	while (*unset && *name && *unset == *name)
	{
		unset++;
		name++;
	}
	if (!*unset && !*name)
		return (1);
	return (0);
}

char	*get_env_name(char *cont)
{
	const char	*tmp;
	char		*dest;
	int			size;
	int			i;

	i = 0;
	size = 0;
	tmp = cont;
	while (*tmp && (isalnum(*tmp) || *tmp == '_'))
	{
		size++;
		tmp++;
	}
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (*cont && (isalnum(*cont) || *cont == '_'))
	{
		dest[i] = *cont;
		cont++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
