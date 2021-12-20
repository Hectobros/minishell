/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dol_is.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:05:23 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 10:25:54 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cut_env_name(char **cont)
{
	(*cont)++;
	while (**cont && (ft_isalnum(**cont) || **cont == '_'))
		(*cont)++;
}

char	*dol_is_env(t_utils *u, char **cont, t_env *lenv)
{
	char	*envname;
	char	*envdata;

	envname = get_env_name(*cont + 1);
	if (!envname)
		return (NULL);
	envdata = get_env42(lenv, envname);
	free(envname);
	if (envdata && *envdata != '\0')
	{
		u->len = u->len + ft_strlen(envdata);
		u->dest = re_alloc(u->dest, u->len, u->i);
		if (!u->dest)
			return (NULL);
		while (*envdata)
			u->dest[u->i++] = *envdata++;
	}
	cut_env_name(cont);
	return (u->dest);
}

char	*dol_is_interrog(t_utils *u, char **cont)
{
	char	*herve;
	int		j;

	j = 0;
	herve = ft_itoa(g_globa.herve);
	u->len = u->len + ft_strlen(herve);
	u->dest = re_alloc(u->dest, u->len, u->i);
	if (!u->dest)
		return (NULL);
	while (herve[j])
		u->dest[u->i++] = herve[j++];
	free(herve);
	(*cont)++;
	(*cont)++;
	return (u->dest);
}
