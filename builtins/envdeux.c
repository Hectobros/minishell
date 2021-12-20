#include "../minishell.h"

int	export_is_valid(char *str)
{
	int	i;

	i = 0;
	if (str[i] > '0' && str[i] < '9')
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		return (1);
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
//	if (str[i] && str[i] == '+' && str[i + 1] == '=' && i > 0)
//		return (0);
	if (str[i] && str[i] == '=' && i > 0)
		return (0);
	if (str[i] && (str[i] > 'a' && *str < 'z')
		&& (str[i] > 'A' && str[i] < 'Z'))
		return (1);
	if (str[i])
		printf("minishell: export: `%s': not a valid identifier\n", str);
	return (1);
}

int	change_existing_value(char *name, char *value, t_env *lst)
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

int	export42(char **cmd, t_env **lst)
{
	int		i;
	int		ret;
	char	*name;
	char	*value;

	i = 1;
	ret = 0;
	while (cmd[i])
	{
		if (!export_is_valid(cmd[i]))
		{
			name = get_env_name(cmd[i]);
			value = get_env_value(cmd[i]);
			if (!change_existing_value(name, value, *lst))
				add_back_env(lst, new_env(name, value));
		}
		else
			ret = 1;
		i++;
	}
	return (ret);
}
