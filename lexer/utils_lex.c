/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:00:24 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 09:18:21 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*get_env42(t_env *lenv, char *name)
{
	char	*envdata;

	while (lenv)
	{
		if (str_comp(lenv->name, name))
		{
			envdata = lenv->value;
			return (envdata);
		}
		lenv = lenv->next;
	}
	return (NULL);
}

char	*re_alloc(char *buff, int hl, int limit)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * hl);
	if (!new)
		return (NULL);
	while (i < limit)
	{
		new[i] = buff[i];
		i++;
	}
	free(buff);
	return (new);
}
