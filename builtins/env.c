/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:14:02 by jvermeer          #+#    #+#             */
/*   Updated: 2021/12/20 02:03:29 by nschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env42(char **cmd, t_env *lst)//ATENTION AU MAIN EN BAS DU FILE
{
	if (cmd[1])
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		return (127);
	}
	while (lst)
	{
		printf("%s=%s\n", lst->name, lst->value);
		lst = lst->next;
	}
	return (0);
}

void	delete_first(t_env **lst)
{
	t_env	*tmp;

	tmp = (*lst);
	*lst = (*lst)->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
}

void	delete_env(t_env *lp, char **cmd, int i)
{
	t_env	*tmp;

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

int	unset_is_valid(char *str)
{
	if (*str > '0' && *str < '9')
		return (1);
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	if (*str)
		return (1);
	return (0);
}

int	unset42(char **cmd, t_env **lst)
{
	int	ret;
	int	i;

	i = 1;
	ret = 0;
	while (cmd[i])
	{
		if (unset_is_valid(cmd[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
			ret = 1;
		}
		else
		{
			if (str_comp((*lst)->name, cmd[i]))
				delete_first(lst);
			else
				delete_env(*lst, cmd, i);
		}
		i++;
	}
	return (ret);
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
