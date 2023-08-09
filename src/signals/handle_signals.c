#include "minishell.h"
#include <errno.h>

void set_signals()
{
    struct sigaction sa;

    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SIG_IGN;

    sigaction(SIGQUIT, &sa, NULL); // ctrl backslash

    sa.sa_handler = handler_sg;
    sigaction(SIGINT, &sa, NULL); // ctrl c
}

void sig_default()
{
    struct sigaction sa;

    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = SIG_IGN;

    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
}

void handler_sg(int num)
{

    if (num == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 1);
        rl_redisplay();
    }
}

void handler_sg_update(int num)
{

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
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handler_sg_update;

    sigaction(SIGQUIT, &sa, NULL); // ctrl backslash
    sigaction(SIGINT, &sa, NULL); // ctrl c
    //sigaction(EOF, &sa, NULL); // ctrl d
}

void modify_terminal_attribut(t_exec *exe)
{
    //(void)struct termios tp;

    if (tcgetattr(STDIN_FILENO, &exe->tp) == - 1)
        fprintf(stderr, "error getattr\n");
    exe->save = exe->tp;
    exe->tp.c_lflag = exe->tp.c_lflag & (~ECHOCTL);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &exe->tp) == -1)
        fprintf(stderr, "error setattr\n");

    //faire fonction pour changer flag a nouveau

    // if (tcgetattr(STDIN_FILENO, &tp) == - 1)
    //     fprintf(stderr, "error getattr\n");
    // tp.c_lflag = tp.c_lflag & (~ECHOCTL);
    // if (tcsetattr(STDIN_FILENO, TCSANOW, &tp) == -1)
    //     fprintf(stderr, "error setattr\n");
}
