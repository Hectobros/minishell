/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dol_is.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 18:05:23 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/16 18:07:11 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(char *cont)
{
	const char	*tmp;
	char		*dest;
	int			size;
	int			i;

	i = 0;
	size = 0;
	tmp = cont;
	while (*tmp && (ft_isalnum(*tmp) || *tmp == '_'))
	{
		size++;
		tmp++;
	}
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (*cont && (ft_isalnum(*cont) || *cont == '_'))
	{
		dest[i] = *cont;
		cont++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	cut_env_name(char **cont)
{
	(*cont)++;
	while (**cont && (ft_isalnum(**cont) || **cont == '_'))
		(*cont)++;
}

char	*dol_is_env(char *new, char **cont, int *i, int *len, t_env *lenv)
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
		*len = *len + ft_strlen(envdata);
		new = re_alloc(new, *len, *i);
		if (!new)
			return (NULL);
		while (*envdata)
			new[(*i)++] = *envdata++;
	}
	cut_env_name(cont);
	return (new);
}

char	*dol_is_interrog(char *new, char **cont, int *i, int *len)
{
	(void)i;
	(void)len;
	(void)new;
	(void)cont;
	new[(*i)++] = *(*cont)++;
	return (new);
}
