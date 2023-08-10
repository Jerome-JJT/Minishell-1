#include "../../minishell.h"

/* ---------------------------- 1.Reset all tab on exec --------------------------------*/
void    reset_shelltab(t_exec *exec)
{
    if(exec->tab_cmd)
    {
        ft_tabreset(&exec->tab_cmd);
        exec->tab_cmd = ft_calloc(20, sizeof(char *));
    }
    if(exec->redi_infile)
    {
        ft_tabreset(&exec->redi_infile);
	    exec->redi_infile = ft_calloc(20, sizeof(char *));
    }
    if (exec->redi_outfile)
    {
        ft_tabreset(&exec->redi_outfile);
	    exec->redi_outfile = ft_calloc(20, sizeof(char *));
    }
    if (exec->heredoc)
    {
        ft_tabreset(&exec->heredoc);
	    exec->heredoc = ft_calloc(20, sizeof(char *));
    }
    if(exec->append)
    {
        ft_tabreset(&exec->append);
        exec->append = ft_calloc(20, sizeof(char *));
    }

}

/* ---------------------------- 2.Variable split --------------------------------*/
char    **split_arg(char *str, int egal, t_dlist **trash)
{
    char    **tab;

    if (egal == 1)
			tab = ft_split(str, '=', trash);
		else
			tab = ft_split_var(str, trash);
    return (tab);
}

/* ---------------------------- 3.Tab --> 1 string --------------------------------*/
char    *tab_to_str(char **tab, t_dlist **trash)
{
    char    *str;
    int     i;

    if (!*tab)
        return (NULL);
    i = 1;
    str = *tab;
	while (tab[i])
	{
		str = ft_strjoin(str, " ", trash);
		str = ft_strjoin(str, tab[i++], trash);
	}
    return (str);
}

/* ---------------------------- 4.Remove quote --------------------------------*/
void    remove_quote(char *str)
{
    int     len;
    int     read;
    int     write;

    if (!str || !*str)
        return ;
    len = ft_strlen(str);
    read = 0;
    write = 0;
    if (*str == '\"')
    {
        while (read < len)
        {
            if (str[read] != '\"')
            {
                str[write] = str[read];
                write++;
            }
            read++;
        }
        str[write] = '\0';
    }
}

/* ---------------------------- 5.Type is sep --------------------------------*/
int type_is_sep(int type)
{
    if (type == PIPE || type == RED_IN || type == RED_OUT
        || type == APPEND || type == H_D)
        return (1);
    return (0);
}
