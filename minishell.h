/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:55:30 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 10:23:39 by jvermeer         ###   ########.fr       */
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
# include <signal.h>
# include <limits.h>

typedef struct s_global
{
	pid_t	pid;
	int		herve;
}		t_global;
typedef struct s_mini
{
	int				pipe[2];
	char			**cmd;
	int				fdin;
	int				fdout;
	int				pid;
	int				content;
	char			*crashword;
	struct s_mini	*next;
	struct s_mini	*prev;
}				t_mini;
typedef struct s_content
{
	int					token;
	char				*content;
	int					pfd[2];
	struct s_content	*next;
}				t_content;
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;
typedef struct s_utils
{
	int		len;
	int		i;
	int		dq;
	char	*dest;
}				t_utils;
extern t_global	g_globa;
int				env42(char **cmd, t_env *lst);
int				exit42(char **cmd);
int				unset42(char **cmd, t_env **lst);
int				export42(char **cmd, t_env **lst);
int				echo42(char **cmd);
int				pwd42(char **cmd);
int				cd42(char **cmd, t_env *lst);
void			put_s(char *s);
void			putstr_and_s(const char *message, char *s);
char			*ft_strjoin(char const *s1, char const *s2);
int				write_error(const char *err, char *s);
char			*re_alloc(char *buff, int hl, int limit);
int				str_comp(char *name, char *unset);
char			*get_env42(t_env *lenv, char *name);
void			add_back(t_content **lst, t_content *lnew);
t_content		*new_lst(char *content);
int				ft_isalnum(int c);
char			*ft_itoa(int n);
char			**ft_split(const char *str, char c);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *src);
int				create_heredoc(t_content *lst, t_env *lenv);
void			remove_quotes(t_content *lst);
int				check_open_quotes(char *str);
int				split_all_content(char *line, t_content **lst);
char			*change_content(char *cont, t_env *lenv);
int				free_content_lst(t_content *lst);
t_env			*new_env(char *name, char *value);
void			add_back_env(t_env **lst, t_env *lnew);
int				free_env(t_env *lst);
char			*get_env_value(const char *env);
int				create_env_lst(t_env **lst, char **env);
char			*get_env_name(char *cont);
char			*dol_is_interrog(t_utils *u, char **cont);
char			*dol_is_env(t_utils *u, char **cont, t_env *lenv);
int				replace_env(t_content *lst, t_env *lenv);
int				make_token(char *rl, t_content **lst, t_env *lenv);
void			add_prev_mini(t_mini *com);
int				len_mini(t_mini *com);
char			*pipe_at_end(char *rl);
int				is_parent(t_mini *l);
int				is_builtin(t_mini *l);
int				dad_is_running(t_mini *l, t_env *lenv);
void			wait_all(t_mini *l);
int				mini_exec(t_mini *l, t_env *lenv, char **env, t_mini *tmp);
void			run_command(t_mini *l, t_env *lenv, char **env, int saveout);
char			*ft_strdupn(const char *s1);
int				ft_lstok(t_content *l);
int				ft_nbpipe(t_content *l);
char			**ft_tabdupgrand(char **tab, char *str);
void			ft_addcom(char *content, t_mini *commande);
int				ft_open(t_content *l, t_mini *com, int token);
int				ft_openone(t_content *l, t_mini *com, int token);
void			ft_opendeux(t_content *l, t_mini *com, int token, int fd);
void			ft_finishcom(t_mini *com, int *fd);
void			ft_createcom(t_mini *com, t_content *l);
t_mini			*ft_createliste(int x);
int				ft_checkcom(t_mini *lcom);
void			ft_freetab(char **content);
int				ft_destroy(t_mini *lcom);
t_mini			*ft_buildpipe(t_content *l, t_env *lenv);
void			*ft_memmove(void *dst, const void *src, size_t len);
t_mini			*ft_lstnewm(int con);
void			ft_lstadd_backm(t_mini **alst, t_mini *n);
t_mini			*ft_lstlastm(t_mini	*lst);
void			ft_printab(char **tab);
int				ft_printcomm(t_mini *com);
int				ft_isdir(t_content *l, t_mini *com);
int				ft_ambigous(t_content *l, t_mini *com, int i);
int				ft_errorsyntax(int x, t_content *l, t_env *lenv);
int				ft_printcomm(t_mini *com);
void			ft_printab(char **tab);
void			routine(int sig);
void			rout(int sig);
void			ft_setsignal(void);
void			ft_delsignal(void);
int				ft_errord(int x);
int				exit2(char **cmd);
void			declare(int ac, char **av, int *exit, t_env **lenv);
int				ctrld(t_env *lenv);

#endif
