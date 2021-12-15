/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:55:30 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/15 11:16:21 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_mini
{
	int		pi[2];
	int		po[2];
	char	**cmd;//cmd name + all flags + argus
	int		fdin;// = -500
	int		fdout;// = -500
	int		content;
	char	*crashword;
	struct s_mini	*next;
}				t_mini;
typedef struct s_content
{
	int					token;// W:1  >:2  >>:3  <:4  <<:5  |:6  if '$no':666
	char				*content;//W = anything O=">"
	int					pfd[2];//reading size: pfd[0]
	struct s_content	*next;
}				t_content;
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

void			add_back(t_content **lst, t_content *lnew);
t_content		*new_lst(char *content);
int				ft_isalnum(int c);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *src);
int				create_heredoc(t_content *lst);
void			remove_quotes(t_content *lst);
int				check_open_quotes(char *str);
int				split_all_content(char *line, t_content **lst);
char			*change_content(char *cont);

char			*get_env_name(char *cont);
char			*get_env_value(const char *env);
int				create_env_lst(t_env **lst, char **env);

#endif
