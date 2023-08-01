#include "minishell.h"

void set_signals()
{
    struct sigaction sa;

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGQUIT, &sa, NULL); // ctrl backslash
    
    sa.sa_handler = handler_sg;
    sigaction(SIGINT, &sa, NULL); // ctrl c
    //sigaction(EOF, &sa, NULL); // ctrl d
}

void handler_sg(int num)
{
    (void)num;
    if (num == SIGINT)
    {
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    // else if (num == EOF)
    // {
    //     fprintf(stderr, "EOF\n");
    //     write(1, "QUIT (core dumped ms)\n", 22);
    //     rl_redisplay();
    // }
}

void handler_sg_update(int num)
{
    (void)num;

    if (num == SIGINT)
    {
	    write(1, "\n", 1);
	    rl_redisplay();
    }
    else if (num == SIGQUIT)
    {
	    write(1, "MS Quit: (core dumped)\n", 23);
	    rl_redisplay();
    }
}

void signals_update()
{
    struct sigaction sa;

    sa.sa_flags = 0;
    sa.sa_handler = handler_sg_update;

    sigemptyset(&sa.sa_mask);
    sigaction(SIGQUIT, &sa, NULL); // ctrl backslash
    sigaction(SIGINT, &sa, NULL); // ctrl c
    //sigaction(EOF, &sa, NULL); // ctrl d
}