#include "minishell.h"

char *find_last_element(char **tab_append_out);
void    create_append_files(char **tab_append_out);

void handle_append(t_exec *exe)
{
    char *last_element;
    char    **tab_append_out;

   // if (!exe->append[exe->idx])   // REMOVED APPEND
   //     exe->last_append = NULL;
   // else
   // {
        tab_append_out = ft_split_exec(exe->append[exe->idx], ' ', 0);
        create_append_files(tab_append_out);
        last_element = find_last_element(tab_append_out);
        if (ft_strncmp("A_", last_element, 2) == 0)
        {
            last_element = (last_element + 2);
            exe->last_append = last_element;
        }
        else
        {
            fprintf(stderr, "append init a NULL\n");
            exe->last_append = NULL;
        }
  //  }
}

char *find_last_element(char **tab_append_out)
{
    int i;

    i = 0;
    while(tab_append_out[i])
        i++;
    i--;
    return(tab_append_out[i]);
}

void    create_append_files(char **tab_append_out)
{
	int i;
	int append;

	i = 0;
    while (tab_append_out[i])
	{
        if (ft_strncmp("A_", tab_append_out[i], 2) == 0)
        {
		    append = open(&tab_append_out[i][2], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (append == -1)
				fprintf(stderr, "error append file opening\n");
		    close(append);
	    }
        i++;
    }
	//i--;
	//exe->redi_outfile[0] = append_tab[i];
	//return (&exe->redi_outfile[0]);
}