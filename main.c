/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/16 11:24:22 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	print_env(t_env *lenv)
{
	while (lenv)
	{
		printf("%s=%s\n", lenv->name, lenv->value);
		lenv = lenv->next;
	}
}

int	free_env(t_env *lst)
{
	t_env	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	return (0);
}

int	free_content_lst(t_content *lst)
{
	t_content	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->content);
		free(tmp);
	}
	return (0);
}

void	print_lst(t_content *lst)
{
	while (lst)
	{
		printf("token:%d  ", lst->token);
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}

char	*re_alloc(char *buff, int hl, int limit)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * hl);
	if (!new)
		return (NULL);
	while (i < limit)
	{
		new[i] = buff[i];
		i++;
	}
	free(buff);
	return (new);
}

/*

void	close_heredoc_pipes(t_content *lst)//      <---- Before ending prog
{
	while (lst)
	{
		if (lst->token == 5)
		{
			close(lst->pfd[0]);
		}
		lst = lst->next;
	}
}
*/

void	give_token(t_content *lst)
{
	char	*tmp;

	while (lst)
	{
		tmp = lst->content;
		if (tmp[0] == '|')
			lst->token = 6;
		else if (tmp[0] == '>' && tmp[1] == '\0')
			lst->token = 2;
		else if (tmp[0] == '>' && tmp[1] == '>')
			lst->token = 3;
		else if (tmp[0] == '<' && tmp[1] == '\0')
			lst->token = 4;
		else if (tmp[0] == '<' && tmp[1] == '<')
			lst->token = 5;
		else
			lst->token = 1;
		lst = lst->next;
	}
}

char	*get_env_name(char *cont)
{
	const char	*tmp;
	char		*dest;
	int			size;
	int			i;

	i = 0;
	size = 0;
	tmp = cont;
	while (*tmp && (ft_isalnum(*tmp) || *tmp == '_'))
	{
		size++;
		tmp++;
	}
	dest = malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	while (*cont && (ft_isalnum(*cont) || *cont == '_'))
	{
		dest[i] = *cont;
		cont++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	cut_env_name(char **cont)
{
	(*cont)++;
	while (**cont && (ft_isalnum(**cont) || **cont == '_'))
		(*cont)++;
}

int	str_comp(char *name, char *unset)
{
	while(*unset && *name && *unset == *name)
	{
		unset++;
		name++;
	}
	if (!*unset && !*name)
		return (1);
	return (0);
}

char	*get_env42(t_env *lenv, char *name)
{
	char *envdata;

	while (lenv)
	{
		if (str_comp(lenv->name, name))
		{
			envdata = lenv->value;
			return(envdata);
		}
		lenv = lenv->next;
	}
	return (NULL);
}

char	*dol_is_env(char *new, char **cont, int *i, int *len, t_env *lenv)
{
	char	*envname;
	char	*envdata;

	envname = get_env_name(*cont + 1);
	if (!envname)
		return (NULL);
//	envdata = getenv(envname);
	envdata = get_env42(lenv, envname);
	free(envname);
	if (envdata && *envdata != '\0')
	{
		*len = *len + ft_strlen(envdata);
		new = re_alloc(new, *len, *i);
		if (!new)
			return (NULL);
		while (*envdata)
			new[(*i)++] = *envdata++;
	}
	cut_env_name(cont);
	return (new);
}

char	*dol_is_interrog(char *new, char **cont, int *i, int *len)
{
	(void)i;
	(void)len;
	(void)new;
	(void)cont;
	new[(*i)++] = *(*cont)++;
	return (new);
}

void	pass_simple_quotes(char **cont, char *new, int *i)
{
	new[(*i)++] = *(*cont)++;
	while (**cont && **cont != '\'')
		new[(*i)++] = *(*cont)++;
	new[(*i)++] = *(*cont)++;
}

char	*change_content(char *cont, t_env *lenv)
{
	char	*new;
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	tmp = cont;
	len = ft_strlen(tmp) + 1;
	new = malloc(sizeof(char) * len);
	while (*tmp)
	{
		if (*tmp == '\'')
			pass_simple_quotes(&tmp, new, &i);
		else if (*tmp == '$' && *(tmp + 1) && *(tmp + 1) == '?')
			new = dol_is_interrog(new, &tmp, &i, &len);
		else if (*tmp == '$' && *(tmp + 1) && (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '_'))
			new = dol_is_env(new, &tmp, &i, &len, lenv);
		else
			new[i++] = *tmp++;
		if (!new)
			return (NULL);
	}
	free(cont);
	new[i] = '\0';
	return (new);
}

char	*check_if_redirection(char *cont, t_env *lenv)
{
	char *tmp;

	tmp = ft_strdup(cont);
	tmp = change_content(tmp, lenv); 
	if (!tmp)
		return (NULL);
	if (*tmp)
	{
		free(tmp);
		return (change_content(cont, lenv));
	}
	free(tmp);
	return (cont);
}

void	del_useless_env(t_content *lst)
{
	t_content *tmp;

	while (lst)
	{
		tmp = lst->next;
		if (tmp && tmp->token == 999)
		{
			lst->next = tmp->next;
			free(tmp->content);
			free(tmp);
		}
		lst = lst->next;
	}
}

int		replace_env(t_content *lst, t_env *lenv)
{
	t_content *before;

	before = lst;
	lst->content = change_content(lst->content, lenv);
	if (!lst->content)
		return (-1);
	lst = lst->next;
	while (lst)
	{
		if (before->token == 1 || before->token == 6)
		{
			lst->content = change_content(lst->content, lenv);
			if (!*lst->content)
				lst->token = 999;
		}
		else if (before->token == 2 || before->token == 3 || before->token == 4)
			lst->content = check_if_redirection(lst->content, lenv);
		if (!lst->content)
			return (-1);
		lst = lst->next;
		before = before->next;
	}
	return (0);
}

void	file_var_inquotes(t_content *lst)
{
	t_content	*bef;
	char		*tmp;

	bef = lst;
	lst = lst->next;
	while (lst)
	{
		tmp = lst->content;
		if ((bef->token == 2 || bef->token == 3 || bef->token == 4) && *tmp == '$'
			&& *(tmp + 1) && (ft_isalnum(*(tmp + 1)) || *(tmp + 1) == '_'))
			lst->token = 666;
		bef = bef->next;
		lst = lst->next;
	}
}

int	make_token(char *rl, t_content **lst, t_env *lenv)
{
	if (ft_strlen(rl) == 0)//-----------------------> code rajouter pour éviter le segfault en cas de ligne vide
		return(0);//---------------------------------> La même
	if (check_open_quotes(rl))
		return (-1);
	if (split_all_content(rl, lst))
		return (33);
	give_token(*lst);
	if (*lst)
		if (replace_env(*lst, lenv))
			return (33);
	del_useless_env(*lst);
	file_var_inquotes(*lst);
	remove_quotes(*lst);
//	read_heredoc(*lst);//temporaire
//	close_heredoc_pipes(*lst);// pour NIELS
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_content	*lst;
	t_env		*lenv;
	int			exit;
	char		*rl;
	const char	*prompt;
//	t_mini		*com;
	(void)ac;
	(void)av;

	exit = 1;
//	com = NULL;
	lenv = NULL;
	create_env_lst(&lenv, env);
//	print_env(lenv);
	prompt = "minishell$ ";
	while (exit)
	{
		lst = NULL;
		rl = readline(prompt);
		if (ft_strlen(rl) != 0)
			add_history(rl);
		if (make_token(rl, &lst, lenv))
		{
			printf("Error\n");
			return (1);
		}
		print_lst(lst);
//		com = ft_buildpipe(lst, lenv);
//		if (com != NULL)
//			ft_printcomm(com);
		free(rl);
		free_content_lst(lst);
		//exit = 0;
	}
	free_env(lenv);
	return (0);
}
