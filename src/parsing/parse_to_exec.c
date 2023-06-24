#include "../../minishell.h"

static char *fill_tab(char *tab, char *token, t_dlist **trash)
{
    print_tab(&tab, "Fill_tab");
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
    return (lst);
}

void pars_to_exec(t_shell *info, t_exec *exec, t_dlist **trash)
{
    int     *pipe;
    t_tok   *tmp;


    pipe = &exec->number_of_pipes;
    tmp = info->token;
    while (tmp)
    {
        if (tmp->type == RED_IN)
            tmp = send_red(tmp, exec, RED_IN, *pipe, trash);
        else if (tmp->type == RED_OUT)
            tmp = send_red(tmp, exec, RED_OUT, *pipe, trash);
        else if (tmp->type == H_D)
            tmp = send_red(tmp, exec, H_D, *pipe, trash);
        else if (ft_isword(tmp->type))
            tmp = send_red(tmp, exec, WORD, *pipe, trash);
        if (!tmp)
            break ;
        if (tmp->type == PIPE)
            *pipe += 1;
        tmp = tmp->next;
    }
    exec->tab_cmd = info->arg;
}