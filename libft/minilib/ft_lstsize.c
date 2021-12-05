/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 12:16:18 by nschmitt          #+#    #+#             */
/*   Updated: 2021/11/17 07:31:36 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		x;
	t_list	*temp;

	x = 1;
	if (lst == NULL)
		return (0);
	temp = lst;
	while (temp->next != NULL)
	{
		x++;
		temp = temp->next;
	}
	return (x);
}
