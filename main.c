/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 10:25:34 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global g_globa;

void	print_env(t_env *lenv)//DEL
{
	while (lenv)
	{
		printf("%s=%s\n", lenv->name, lenv->value);
		lenv = lenv->next;
	}
}

void	print_lst(t_content *lst)//DEL
{
	while (lst)
	{
		printf("token:%d  ", lst->token);
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}









int	main(int ac, char **av, char **env)
{
	t_content	*lst;
	t_env		*lenv;
	char		*rl;
	const char	*prompt;
	t_mini		*com;
	int			ret;
	(void)ac; (void)av;
	int			exit = 1;

	g_globa.herve = 0;
	com = NULL;
	lenv = NULL;
	create_env_lst(&lenv, env);
	//	print_env(lenv);
	prompt = "minishell$ ";
	while (exit)
	{
		g_globa.pid = -1;
		lst = NULL;
		ft_setsignal();
		rl = readline(prompt);
		if (rl == NULL)
		{
			rl_clear_history();
			free_env(lenv);
			printf("exit\n");
			return(0);
		}
		rl = pipe_at_end(rl);
		if (ft_strlen(rl) != 0)
			add_history(rl);
		if (!make_token(rl, &lst, lenv))
		{
			//		print_lst(lst);
			com = ft_buildpipe(lst, lenv);
			add_prev_mini(com);

			free_content_lst(lst);
			free(rl);

			//		if (com != NULL)
			//						ft_printcomm(com);

			if (len_mini(com) == 1 && is_parent(com))
			{
				ret = dad_is_running(com, lenv);
				if (ret == 888)
					exit = 0;
				else
					g_globa.herve = ret;
			}
			else
			{
				if (mini_exec(com, lenv, env, com))
					return (1);
				wait_all(com);
			}
			ft_destroy(com);
		}
		//		exit = 0;
		//		printf("glo:%d\n", globa.herve);
	}
	rl_clear_history();
	free_env(lenv);
	return (g_globa.herve);
}
