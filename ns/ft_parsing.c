#include "../minishell.h"
# include <sys/types.h>

// to do :
// gérer les $
// gérer les dir en Input -> gérer
// faire ft_error pour print comme il faut -> cas spécial pour ambigous redir -> géré pour les syntax
// faire une fonction pour tout free proprement
// creat_heredoc

int	ft_spheredoc(t_content *l, int x)
{
	l->token++;
	l->token--;
	return (x);
}

int	ft_lstok(t_content *l) // vérifie les erreur obvious dans la liste
{
	int previous;
	t_content *lst;

	lst = l;
	previous = 0;
	while(lst != NULL)
	{
		if (previous == 0 && lst->token == 6)
			return (ft_spheredoc(l, 16));//syntax error near unexpected token
		if ((previous != 0 && previous != 1) && (!(lst->token == 1 || lst->token == 666)))
			return (ft_spheredoc(l, 10 + lst->token));//syntax error near unexpected token
		previous = lst->token;
		lst = lst->next;
	}
	if (previous != 1 && previous != 0 && previous != 666)
		return(ft_spheredoc(l,10));//syntax error near unexpected token `newline'
	return (0);
}

int	ft_nbpipe(t_content *l) // calcul le nombre de pipe et renvoie + 1 afin de créer la liste de commande
{
	t_content *lst;
	int nbpipe;

	lst = l;
	nbpipe = 1;
	while (lst)
	{
		if (lst->token == 6)
			nbpipe++;
		lst = lst->next;
	}
	return (nbpipe);
}

char **ft_tabdupgrand(char **tab, char *str) // permet de dupliquer le tableau de la commande
{
	int x;
	int y;
	char **temp;

	x = 0;
	y = 0;
	while (tab[x])
		x++;
	temp = malloc(sizeof(char *) * (x + 2));
	while (y < x)
	{
		temp[y] = tab[y];
		y++;
	}
	free(tab);
	temp[y] = str;
	temp[y + 1] = NULL;
	return (temp);
}

void	ft_addcom(char *content, t_mini *commande) // permet d'ajouter un mot dans la cda
{
	if (commande->cmd == NULL)
	{
		commande->cmd = malloc(sizeof(char *) * 2);
		commande->cmd[0] = ft_strdup(content);
		commande->cmd[1] = NULL;
	}
	else
		commande->cmd = ft_tabdupgrand(commande->cmd, ft_strdup(content));
}

int	ft_isdir(t_content *l, t_mini *com)
{
	int x;
	struct stat path_stat;
	stat(l->content, &path_stat);
	x = S_ISDIR(path_stat.st_mode);
	if (x == 0)
		return (0);
	else
	{
		com->fdout = -3;
		if (com->crashword == NULL)
			com->crashword = ft_strdupn(l->content);
		return (-1);
	}
}

int	ft_ambigous(t_content *l, t_mini *com, int i)
{
	if (l->token == 666)
	{
		printf("HERE");
		if (i == 0)
			com->fdin = -2;
		if (i == 1)
			com->fdout = -2;
		com->crashword = l->content;
		return (-1);
	}
	else
		return (0);
}

int ft_open(t_content *l, t_mini *com, int token) // sert a open les input et output
{
	int fd;

	fd = 0; // le compileur me casse les couilles useless en soit
	if (token == 2 || token == 3)
	{
		if (com->fdout >= 0)
			close(com->fdout);
		if (ft_isdir(l->next, com) != 0)// gestion des directory, a faire crash pendant l'exec
			return(-3);
		if (ft_ambigous(l->next, com, 1) != 0)
			return(-2);	
		else if (token == 2)
		{
			com->fdout = open(l->next->content, O_WRONLY|O_CREAT|O_TRUNC, 0644);
			if (com->fdout == -1)
				com->crashword = ft_strdup(l->next->content);
		}
		else 
		{
			com->fdout = open(l->next->content, O_WRONLY|O_CREAT|O_APPEND, 0644);
			if (com->fdout == -1)
				com->crashword = ft_strdup(l->next->content);
		}
		fd = com->fdout;
	}
	else if (token == 4 || token == 5)
	{
		if (com->fdin != -500)
			close(com->fdin);
		if (ft_ambigous(l->next, com, 0) != 0)
			return(-2);
		if (token == 4)
		{
			com->fdin = open(l->next->content, O_RDONLY);
			if (com->fdin == -1)
			{
				fd = access(l->next->content, F_OK);
				if (!fd)
					com->fdin = -1;
				else
					com->fdin = -4;
				com->crashword = ft_strdup(l->next->content);
			}
		}
		else if (token == 5)
			com->fdin = l->pfd[0];//----------------------------------------------------------------------------------->
		fd = com->fdin;
	}
	return (fd);
}

void	ft_finishcom(t_mini *com, int *fd)
{
	int x;
	*fd = 0;
	x = com->content + 1;
	x++;
	//fonction qui sert a r met qui devra surement être utiliser plus tard 
}

void	ft_createcom(t_mini *com, t_content *l)// fonction générale pour créer la commande
{
//	int x;
	int fd;
	t_content *lst;
	t_mini *lstcom;

//	x = 0;
	fd = 0;
	lst = l;
	lstcom = com;
	while(lst)
	{
		if (lst->token >= 2 && lst->token <= 5 && fd != -766)// si un fd stdin a crash on arrete de lire jusqu'a la pipe
		{
			fd = ft_open(lst, lstcom, lst->token);
			if (fd == -1 || fd == -2 || fd == -3)
				fd = -766;// rentrer un pointeur sur fd pour gagner des lignes
			lst = lst->next;
		}
		else if (lst->token == 1 && fd != -766)
			ft_addcom(lst->content, lstcom);
		else if (lst->token == 6)
		{
			ft_finishcom(lstcom, &fd);
			lstcom = lstcom->next;
		}
		lst = lst->next;
	}
}

t_mini	*ft_createliste(int x) // permet de créer la liste de commande
{
	t_mini *start;
	int y;

	y = 0;
	start = ft_lstnewm(y);
	y++;
	while (y < x)
	{
		ft_lstadd_backm(&start, ft_lstnewm(y));
		y++;
	}
	return (start);
}

int	ft_checkcom(t_mini *lcom) //vérifie la valider des commandes 
{
	t_mini *copy;
	int r;

	r = 0;
	copy = lcom;
	while (copy)
	{
		if (copy->fdin == -1)
		{
			write(1, "Error fdin", 1);
			r = -1;
		}
		copy = copy->next;
	}
	return (r);
}

void	ft_freetab(char **content)
{
	int x;

	x = 0;

	if (content == NULL)
		return;
	while(content[x])
	{
		free(content[x]);
		x++;
	}
	free(content);
}

int ft_destroy(t_mini *lcom)
{
	t_mini *temp;

	while (lcom)
	{
		if (lcom->fdin > 0)
			close(lcom->fdin);
		if (lcom->fdout > 0)
			close(lcom->fdout);
		if (lcom->crashword)
			free(lcom->crashword);
		//if (lcom->content)
		//	free(lcom->content);
		if (lcom->cmd)
			ft_freetab(lcom->cmd);
		temp = lcom;
		lcom = lcom->next;
		free(temp);
	}
	return (1);
}
/*
int ft_execheredoc(t_content *l)
{
	t_content *lst;
	int fd;

	lst = l;
	while (lst != NULL)
	{
		if (lst->token == 5)
		{
			fd = open_heredoc(lst);//----------------------------------------------------------------------------------------------->
			close(fd);
		}
		if (lst->token == -123)
			lst = NULL;
		lst->next;
	}
	return (-1);
}*/

int	ft_errorsyntax(int x, t_content *l, t_env *lenv)
{
	if (x == 0)
		return 0;
	if (x == 10)
	{
		create_heredoc(l, lenv);
		return(write(1, "syntax error near unexpected token `newline'\n", 45));
	}
	create_heredoc(l, lenv);
	if (x == 12)
		return(write(1, "syntax error near unexpected token `>'\n", 39));
	if (x == 13)
		return(write(1, "syntax error near unexpected token `>>'\n", 40));
	if (x == 14)
		return(write(1, "syntax error near unexpected token `<'\n", 39));
	if (x == 15)
		return(write(1, "syntax error near unexpected token `<<'\n", 40));
	if (x == 16)
		return(write(1, "syntax error near unexpected token `|'\n", 39));
	return (1);
}

t_mini	*ft_buildpipe(t_content *l, t_env *lenv) // main fonction
{
	//int nbcom;
	t_mini *lcom;
	//int error;

	lcom = NULL;
	if (l == NULL)// a voir si ça reste juste une protection contre entrer une ligne vide
		return NULL;
	if (ft_errorsyntax(ft_lstok(l), l, lenv) != 0)
	{
		return NULL;// check pour les double redir et crash commun on devra surement rajouter vérifier les dir en output
	}
	create_heredoc(l, lenv);
	lcom = ft_createliste(ft_nbpipe(l));// calcule combien de pipe et créer la liste en fonction
	ft_createcom(lcom, l);//explose les token pour obtenir une liste chainée contenant toutes les commandes + fdin/fdout
	//if (ft_checkcom(lcom) == -1)
	//	return NULL;
	return (lcom);
}

void ft_printab(char **tab)
{
	int x;

	x = 0;
	while (tab[x] != NULL)
	{
		printf("%s ,",tab[x]);
		x++;
	}
	printf("\n");
}

int ft_printcomm(t_mini *com)
{
	while (com)
	{
		printf("-----COMMANDE N°%d-------\n", com->content);
		if (com->cmd)
			ft_printab(com->cmd);
		printf("FDIN:%d\n", com->fdin);
		printf("FDOUT:%d\n", com->fdout);
		if (com->crashword != NULL)
		printf("CRASHWORD: %s\n", com->crashword);
		printf("-----FIN DE COMMANDE------\n");
		com = com->next;
	}
	return 0;
}
