#include "../../minishell.h"

static char *fill_tab(char *tab, char *token, t_dlist **trash)
{
    if (!tab)
        tab = ft_strdup(token, trash);
    else
    {
        tab = ft_strjoin(tab, " ", trash);
        tab = ft_strjoin(tab, token, trash);
    }
    return (tab);
}

static t_tok    *send_red(t_tok *lst, t_exec *exec, int type, int index, t_dlist **trash) 
{
    if (type == WORD)
        exec->tab_cmd[index] = fill_tab(exec->tab_cmd[index], lst->tok, trash);
    else
    {
        lst = lst->next;
        if (lst->type == SPACE)
            lst = lst->next;
        if (type == RED_IN)
            exec->redi_infile[index] = fill_tab(exec->redi_infile[index], lst->tok, trash);
        else if (type == RED_OUT)
           exec->redi_outfile[index] = fill_tab(exec->redi_outfile[index], lst->tok, trash);
        else if (type == H_D)
            exec->heredoc[index] = fill_tab(exec->heredoc[index], lst->tok, trash);
    }
 //   exec->append = tab_test_append;
    return (lst);
}

void pars_to_exec(t_shell *info, t_exec *exec, t_dlist **trash)
{
    int     pipe;
    int     in;
    int     out;
    int     hd;
    t_tok   *tmp;
    char *test_append[] = {NULL};

    pipe = 0;
    in = -1;
    out = -1;
    hd = -1,
    tmp = info->token;
    exec->append = test_append;
    while (tmp)
    {
        if (tmp->type == RED_IN)
            tmp = send_red(tmp, exec, RED_IN, ++in, trash);
        else if (tmp->type == RED_OUT)
            tmp = send_red(tmp, exec, RED_OUT, ++out, trash);
        else if (tmp->type == H_D)
            tmp = send_red(tmp, exec, H_D, ++hd, trash);
        else if (ft_isword(tmp->type))
            tmp = send_red(tmp, exec, WORD, pipe, trash);
        if (!tmp)
            break ;
        if (tmp->type == PIPE)
            pipe++;
        tmp = tmp->next;
    }
    exec->number_of_pipes = pipe;
}