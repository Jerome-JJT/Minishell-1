#include "minishell.h"

char *find_last_element(char **tab_append_out);
void    create_append_files(char **tab_append_out);
void find_append_doublon(t_exec *exe, char **tab_append);
void pre_handle_append(t_exec *exe);

void pre_handle_append(t_exec *exe)
{
    char    **tab_append_to_compare;
    char    **tab_append_out;
    char    *last_element;
    int i;

    i = exe->number_of_pipes;
    tab_append_to_compare = my_malloc((i + 1), sizeof(char**), exe->trash_lst_exe);
    tab_append_to_compare[i + 1] = NULL;
    while(i >= 0)
    {
        if (exe->append[i])
        {
            tab_append_out = ft_split_exec(exe->append[i], ' ', 0);
            last_element = find_last_element(tab_append_out);
            if (ft_strncmp("A_", last_element, 2) == 0)
            {
                last_element = (last_element + 2);
                tab_append_to_compare[i] = last_element;
            }
        }
        else
            tab_append_to_compare[i] = NULL;
        i--;
    }
    i = 0;
    while (tab_append_to_compare[i])
    {
       // fprintf(stderr, "tab_app_to_cmp[%d]: %s\n", i, tab_append_to_compare[i]);
        i++;
    }
    exe->append_first_cmd = tab_append_to_compare[0];
    find_append_doublon(exe, tab_append_to_compare);
    //fprintf(stderr, "exe->append_first_cmd: %s\n", exe->append_first_cmd);
}

void find_append_doublon(t_exec *exe, char **tab_append)
{
    int i;

    i = exe->number_of_pipes;
    while(i > 0)
    {
        //fprintf(stderr, "append first: %s et tab_append[%d]; %s\n", exe->append_first_cmd, i, tab_append[i]);
        if(tab_append[i] && ft_strcmp(exe->append_first_cmd, tab_append[i]) == 0)
        {
            exe->idx_doublon_append = i;
            break;
        }
        i--;
    }
   // fprintf(stderr, "idx_doublon_append : %d\n", exe->idx_doublon_append);
}
