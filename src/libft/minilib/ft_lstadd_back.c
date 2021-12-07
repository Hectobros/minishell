/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 12:16:18 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/17 07:28:47 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*temp;

	if (alst == NULL || new == NULL)
		return ;
	temp = *alst;
	temp = ft_lstlast(temp);
	if (temp != NULL)
		temp->next = new;
	if (temp == NULL)
		*alst = new;
	return ;
}
