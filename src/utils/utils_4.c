#include "../../minishell.h"

void    reset_exectab(t_exec *exec)
{
    if (exec->tab_cmd)
        ft_tabreset(exec->tab_cmd);
    if (exec->redi_infile)
        ft_tabreset(exec->redi_infile);
    if (exec->redi_outfile)
        ft_tabreset(exec->redi_outfile);
    if (exec->heredoc)
        ft_tabreset(exec->heredoc);
}