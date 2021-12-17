/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:14:02 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/17 20:34:25 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env42(char **cmd, t_env *lst)
{
	(void)cmd;
	printf("here:%s\n", lst->name);
	printf("HEEEY");
	while (lst)
	{
		putstr_and_s("%s=", lst->name);
		putstr_and_s("%s\n", lst->value);
		lst = lst->next;
	}
	exit(0);
}

void	delete_first(t_env **lst)
{
	t_env *tmp;

	tmp = (*lst);
	*lst = (*lst)->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
}
 
void	delete_env(t_env *lp, char **cmd, int i)
{
	t_env *tmp;

	while (lp)
	{
		tmp = lp->next;
		if (tmp && str_comp(tmp->name, cmd[i]))
		{
			lp->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
		}
		lp = lp->next;
	}
}

void	unset42(char **cmd, t_env **lst)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (str_comp((*lst)->name, cmd[i]))
			delete_first(lst);
		else
			delete_env(*lst, cmd, i);
		i++;
	}
}

int		export_is_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (isalnum(str[i]) || str[i] == '_'))
		i++;
	if (str[i] && str[i] == '=')
		exit(1);
	return (0);
}

int		change_existing_value(char *name, char *value, t_env *lst)
{
	while (lst)
	{
		if (str_comp(name, lst->name))
		{
			free(lst->value);
			free(name);
			lst->value = value;
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

void	export42(char **cmd, t_env **lst)
{
	int		i;
	char	*name;
	char	*value;

	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '=')
			write_error("export: '%s': not a valid identifier\n", cmd[i]);
		if (export_is_valid(cmd[i]))
		{
			name = get_env_name(cmd[i]);
			value = get_env_value(cmd[i]);
			if (!change_existing_value(name, value, *lst))
				add_back_env(lst, new_env(name, value));
		}
		i++;
	}
	exit(0);
}
/*
int	main(int ac, char **av, char **env)
{
	t_env		*lenv;
	char		**envcmd;
	char		**unset;
	char		**export;
	(void)av;
	(void)ac;
	(void)unset;
	(void)envcmd;

	lenv = NULL;
	create_env_lst(&lenv, env);
	envcmd = malloc(sizeof(char*) * 8);
	unset = malloc(sizeof(char*) * 8);
	export = malloc(sizeof(char*) * 8);
	envcmd[0] = strdup("env");
	envcmd[1] = NULL;

	unset[0] = strdup("unset");
	unset[1] = strdup("GJS_DEBUG_TOPICS");
	unset[2] = NULL;

	export[0] = strdup("export");
	export[1] = strdup("LSC=");
	export[3] = strdup("NN=159");
	export[2] = strdup("LSC=hey");
	export[4] = NULL;

//	unset42(unset, &lenv);
	env42(env, lenv);
	printf("\n");
	export42(export, &lenv);
	env42(env, lenv);

	free_env(lenv);
	free(envcmd[0]);
	free(envcmd);
	free(unset[0]);
	free(unset[1]);
	free(unset);
	return (0);
}
*/
