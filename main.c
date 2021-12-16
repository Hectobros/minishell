/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschmitt <nschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 10:33:55 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/16 20:03:13 by jvermeer         ###   ########.fr       */
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
void	print_lst(t_content *lst)
{
	while (lst)
	{
		printf("token:%d  ", lst->token);
		printf("%s\n", lst->content);
		lst = lst->next;
	}
}
/*
   void	close_heredoc_pipes(t_content *lst)//      <---- If parsing failed
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




void	add_prev_mini(t_mini *com)
{
	t_mini	*tmp;

	tmp = NULL;
	while (com)
	{
		com->prev = tmp;
		tmp = com;
		com = com->next;
	}
}


void	execution(t_mini *l)
{
	while (l)
	{
		if (l->prev)
			close(l->pin[1]);
		if (l->next)
			pipe(l->pout);

	}
}



int	main(int ac, char **av, char **env)
{
	t_content	*lst;
	t_env		*lenv;
	char		*rl;
	const char	*prompt;
	t_mini		*com;
	(void)ac; (void)av;
	int			exit = 1;

	com = NULL;
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
		com = ft_buildpipe(lst, lenv);
		add_prev_mini(com);
		if (com != NULL)
			ft_printcomm(com);

		execution(com);

		free(rl);
		free_content_lst(lst);
		//		exit = 0;
	}
	free_env(lenv);
	return (0);
}
