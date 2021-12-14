/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnewmini.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 12:16:18 by nschmitt          #+#    #+#             */
/*   Updated: 2021/12/12 20:18:50 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_mini	*ft_lstnewm(int con)
{
	t_mini	*new;

	new = malloc(sizeof(t_mini));
	if (new == NULL)
		return (NULL);
	new->content = con;
	new->cmd = NULL;
	new->next = NULL;
	new->fdin = -500;
	new->fdout = -500;
	new->crashword = NULL;
	return (new);
}
