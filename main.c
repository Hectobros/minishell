/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 11:12:11 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_globa;

void	print_env(t_env *lenv)
{
	while (lenv)
	{
		printf("%s=%s\n", lenv->name, lenv->value);
		lenv = lenv->next;
	}
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

int	lexer_ok(char *rl, t_content *lst, t_env *lenv, char **env)
{
	t_mini	*com;
	int		ret;

	com = NULL;
	free(rl);
	com = ft_buildpipe(lst, lenv);
	free_content_lst(lst);
	add_prev_mini(com);
	if (len_mini(com) == 1 && is_parent(com))
	{
		ret = dad_is_running(com, lenv);
		if (ret == 888)
			return (0);
		g_globa.herve = ret;
	}
	else
	{
		if (mini_exec(com, lenv, env, com))
			return (1);
		wait_all(com);
	}
	ft_destroy(com);
	return (1);
}

int	ctrld(t_env *lenv)
{
	rl_clear_history();
	free_env(lenv);
	printf("exit\n");
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_content	*lst;
	t_env		*lenv;
	char		*rl;
	int			exit;

	declare(ac, av, &exit, &lenv);
	g_globa.herve = 0;
	create_env_lst(&lenv, env);
	while (exit)
	{
		lst = NULL;
		g_globa.pid = -1;
		ft_setsignal();
		rl = readline("minishell$ ");
		if (rl == NULL)
			return (ctrld(lenv));
		rl = pipe_at_end(rl);
		if (ft_strlen(rl) != 0)
			add_history(rl);
		if (!make_token(rl, &lst, lenv))
			exit = lexer_ok(rl, lst, lenv, env);
	}
	rl_clear_history();
	free_env(lenv);
	return (g_globa.herve);
}
