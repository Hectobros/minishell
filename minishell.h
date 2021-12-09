/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:55:30 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/09 18:49:59 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_tree
{
	int		pipe;//pipe=1 or pipe=0


	int		redirection; //table des redir: >:1   >>:10  <:15 <<:20  ou 0
	char	**cmd;//cmd name + all flags + argus
	char	*input;
	char	*ouput; //NULL ? 

}				t_tree;


// 	< file1 > file2 cmd1 arg1 flag1 | 

typedef struct s_content
{
	int					word;// W=1  O=0
	char				*content;//W = anything O=">"
	struct s_content	*next;
}				t_content;

void			add_back(t_content **lst, t_content *lnew);
t_content		*new_lst(char *content);

size_t		ft_strlen(const char *s);
int			check_open_quotes(char *str);

#endif
