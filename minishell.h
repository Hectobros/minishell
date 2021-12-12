/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:55:30 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/12 17:15:19 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_mini
{
	int		pi[2];
	int		po[2];
//	int		piperedir[2];
	char	**cmd;//cmd name + all flags + argus
	int		fdin;// = -500
	int		fdout;// = -500
	struct s_mini	*next;
}				t_mini;

typedef struct s_content
{
	int					token;// W:1  >:2  >>:3  <:4  <<:5  |:6
	char				*content;//W = anything O=">"
	int					pipe[2];
	//create function close all pipe
	struct s_content	*next;
}				t_content;

void			add_back(t_content **lst, t_content *lnew);
t_content		*new_lst(char *content);

int			ft_isalnum(int c);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *src);
int			check_open_quotes(const char *str);

#endif
