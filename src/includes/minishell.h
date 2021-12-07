#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/ft_printf.h"

void	ft_clean();
char	*rl_get(char *line_read);

#endif
