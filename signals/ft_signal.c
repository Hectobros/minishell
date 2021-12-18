#include "../minishell.h"

void    routine(int sig)
{
    if (globa.pid != -1)
    {
        kill(globa.pid, sig);
        globa.pid = -1;
        printf("\n");
    }
    else if (globa.pid)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void    rout(int sig)
{
    if (globa.pid != -1)
    {
        kill(globa.pid, sig);
        printf("Quit (core dumped)\n");
        globa.pid = -1;
    }
    else
        write(1,"\b\b  \b\b", 6);
    (void)sig;
}

void    ft_setsignal()
{
    signal(SIGINT, &routine);
    signal(SIGQUIT, &rout);
}

void    ft_delsignal()
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}
