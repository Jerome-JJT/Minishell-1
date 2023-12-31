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
    char    *tmp;

    tmp = NULL;
    // printf("lst->tok: %s\n", lst->tok);
    if (ft_isword(type))
        exec->tab_cmd[index] = fill_tab(exec->tab_cmd[index], lst->tok, trash);
    else
    {
        lst = lst->next;
        // printf("lst->tok: %s\n", lst->tok);
        if (lst->type == SPACEE)
            lst = lst->next;
        if (type == RED_IN)
            exec->redi_infile[index] = fill_tab(exec->redi_infile[index], lst->tok, trash);
        else if (type == RED_OUT)
        {
            tmp = ft_strjoin("O_", lst->tok, trash);
            exec->append[index] = fill_tab(exec->append[index], tmp, trash);
            exec->redi_outfile[index] = fill_tab(exec->redi_outfile[index], lst->tok, trash);
        }
        else if (type == APPEND)
        {
            tmp = ft_strjoin("A_", lst->tok, trash);
            exec->append[index] = fill_tab(exec->append[index], tmp, trash);
        }
        else if (type == H_D)
        {
            exec->heredoc[index] = fill_tab(exec->heredoc[index], lst->tok, trash);
            lst = lst->next;
        }
    }
    return (lst);
}

void pars_to_exec(t_shell *info, t_exec *exec, t_dlist **trash)
{
    int     pipe;
    t_tok   *tmp;

    pipe = 0;
    tmp = info->token;
    // print_token(&info->token, "Test pars_to_exec");
    while (tmp)
    {
        if (tmp->type == RED_IN)
            tmp = send_red(tmp, exec, RED_IN, pipe, trash);
        else if (tmp->type == RED_OUT)
            tmp = send_red(tmp, exec, RED_OUT, pipe, trash);
        else if (tmp->type == APPEND)
            tmp = send_red(tmp, exec, APPEND, pipe, trash);
        else if (tmp->type == H_D)
            tmp = send_red(tmp, exec, H_D, pipe, trash);
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