/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:55:30 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/14 19:33:14 by nschmitt         ###   ########.fr       */
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
# include <sys/stat.h>
# include <fcntl.h>

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

//fonctions Niels
char	*ft_strdupn(const char *s1);
int	ft_lstok(t_content *l);
int	ft_nbpipe(t_content *l);
char **	ft_tabdupgrand(char **tab, char *str);
void	ft_addcom(char *content, t_mini *commande);
int ft_open(t_content *l, t_mini *com, int token);
void	ft_finishcom(t_mini *com, int *fd);
void	ft_createcom(t_mini *com, t_content *l);
t_mini	*ft_createliste(int x);
int	ft_checkcom(t_mini *lcom);
void	ft_freetab(char **content);
int ft_destroy(t_mini *lcom);
t_mini	*ft_buildpipe(t_content *l);
void	*ft_memmove(void *dst, const void *src, size_t len);
t_mini	*ft_lstnewm(int con);
void	ft_lstadd_backm(t_mini **alst, t_mini *n);
t_mini	*ft_lstlastm(t_mini	*lst);
void	ft_freetab(char **content);
void ft_printab(char **tab);
int ft_printcomm(t_mini *com);
int	ft_spheredoc(t_content *l, int x);
int	ft_isdir(t_content *l, t_mini *com);
int	ft_ambigous(t_content *l, t_mini *com, int i);
int	ft_errorsyntax(int x, t_content *l);
int ft_printcomm(t_mini *com);
void ft_printab(char **tab);

#endif
