#include "minishell.h"

void handle_signals(int sig_num)
{
    fprintf(stderr, "signals number : %d\n", sig_num);
    if (sig_num == SIGINT ) // ctrl c
    {
       // fprintf(stderr, "if sig num == 2\n");
       // write(1, "^C\n", 3);
        // rl_on_new_line();
        // rl_replace_line("", 0);
        // rl_redisplay();
    }
    if (sig_num == SIGQUIT)
    {
        fprintf(stderr, "SIGQUIT: %d\n", sig_num);
    }
    signal(sig_num, SIG_DFL);
}