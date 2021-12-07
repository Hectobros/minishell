#include "includes/minishell.h"

void	ft_clean()
{
	clear_history();
}

char *rl_get(char *line_read)
{
	
	line_read = readline ("minishell>>>");
	if (ft_strlen(line_read) != 0)
		add_history (line_read);
	return (line_read);
}

int main()
{
	char *line;

	line = NULL;
	while (1)
	{
		line = rl_get(line);
		printf("%s\n",line);
	}
	ft_clean();
}
