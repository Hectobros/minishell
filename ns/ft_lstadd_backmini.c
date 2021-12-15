/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_backmini.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 12:16:18 by nschmitt          #+#    #+#             */
/*   Updated: 2021/12/12 20:26:48 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_backm(t_mini **alst, t_mini *n)
{
	t_mini	*temp;

	if (alst == NULL || n == NULL)
		return ;
	temp = *alst;
	temp = ft_lstlastm(temp);
	if (temp != NULL)
		temp->next = n;
	if (temp == NULL)
		*alst = n;
	return ;
}
