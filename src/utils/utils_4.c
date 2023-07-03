#include "../../minishell.h"

void    reset_shelltab(t_exec *exec, t_shell *shell)
{
    ft_free_2da(exec->tab_cmd, NULL);
    ft_free_2da(exec->redi_infile, NULL);
    ft_free_2da(exec->redi_outfile, NULL);
    ft_free_2da(exec->heredoc, NULL);
    ft_dlst_clear(&shell->trash_lst, free);
    exec->tab_cmd = ft_calloc(100, sizeof(char *));
	exec->heredoc = ft_calloc(100, sizeof(char *));
	exec->redi_infile = ft_calloc(100, sizeof(char *));
	exec->redi_outfile = ft_calloc(100, sizeof(char *));
    shell->trash_lst = ft_calloc(1, sizeof(t_dlist));
}

// void    reset_exectab(t_exec *exec)
// {
//     if (exec->tab_cmd)
//         ft_tabreset2(exec->tab_cmd, exec);
//     if (exec->redi_infile)
//         ft_tabreset2(exec->redi_infile, exec);
//     if (exec->redi_outfile)
//         ft_tabreset2(exec->redi_outfile, exec);
//     if (exec->heredoc)
//         ft_tabreset2(exec->heredoc, exec);
// }