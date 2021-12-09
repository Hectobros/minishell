/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:55:30 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/09 11:48:13 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_content
{
	int					pipe;
	int					word;
	char				*content;
	struct s_content	*next;
}				t_content;
void			add_back(t_content **lst, t_content *lnew);
t_content		*new_lst(char *content);

size_t		ft_strlen(const char *s);
int			check_open_quotes(char *str);

#endif
