/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:55:30 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/10 17:36:33 by jvermeer         ###   ########.fr       */
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
	int					token;// W:1  >:2  >>:3  <:4  <<:5  |:6
	char				*content;//W = anything O=">"
	struct s_content	*next;
}				t_content;

void			add_back(t_content **lst, t_content *lnew);
t_content		*new_lst(char *content);

int			ft_isalnum(int c);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *src);
int			check_open_quotes(const char *str);

#endif
