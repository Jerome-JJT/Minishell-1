#include "../../minishell.h"

void    reset_shelltab(t_exec *exec, t_shell *shell)
{

	(void) shell;
    ft_tabreset(exec->tab_cmd);
    ft_tabreset(exec->redi_infile);
    ft_tabreset(exec->redi_outfile);
    ft_tabreset(exec->heredoc);
    ft_free_2da(exec->tab_cmd, NULL);
    ft_free_2da(exec->redi_infile, NULL);
    ft_free_2da(exec->redi_outfile, NULL);
    ft_free_2da(exec->heredoc, NULL);
    // print_trash(&shell->trash_lst);
    // ft_dlst_clear(&shell->trash_lst, free);
	exec->heredoc = ft_calloc(20, sizeof(char *));
	exec->redi_infile = ft_calloc(20, sizeof(char *));
	exec->redi_outfile = ft_calloc(20, sizeof(char *));
    exec->tab_cmd = ft_calloc(20, sizeof(char *));
    // shell->trash_lst = ft_calloc(1, sizeof(t_dlist));
    // if (exec->tab_cmd)
    // if (exec->redi_infile)
    // if (exec->redi_outfile)
    // if (exec->heredoc)
}
