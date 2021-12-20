/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:45:54 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 09:17:25 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
