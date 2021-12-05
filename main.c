#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/ft_printf.h"

int ft_exit(char *s)
{
	int x;
	char *p;

	x = 0;
	p = "exit";
	if (s == NULL)
		return (1);
	while (p[x] == s[x] && p[x] && s[x])
	{
		if (!p[x])
			return (-1);
		x++;
	}
	if (x == 5)
		return(0);
	return (1);
}

int main()
{
	char * test;

	test = NULL;
	while (ft_exit(test) != 0)
	{
		printf("\033[0;32m");	
		test = readline("\nminishell:\033[0m");		
		printf("\033[0m");	
		printf("\033[0;31m");	
		printf("%s",test);
		printf("\033[0m");	
	}
}
