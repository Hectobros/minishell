/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_content_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:45:54 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/15 11:54:09 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_content	*new_lst(char *content)
{
	t_content	*lnew;

	lnew = malloc(sizeof(t_content));
	if (lnew == NULL)
		return (NULL);
	lnew->content = content;
	lnew->next = NULL;
	return (lnew);
}

t_content	*last_ptr(t_content *lst)
{
	t_content	*lret;

	lret = NULL;
	while (lst)
	{
		lret = lst;
		lst = lst->next;
	}
	return (lret);
}

void	add_back(t_content **lst, t_content *lnew)
{
	t_content	*ltmp;

	if (*lst)
	{
		ltmp = last_ptr(*lst);
		ltmp->next = lnew;
	}
	else
		*lst = lnew;
}
