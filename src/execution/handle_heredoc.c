#include "minishell.h"

int handle_heredoc(t_exec *d_exe)
{
    int		i;
    int		size;
    char	*buffer = NULL;
	char	**heredoc_tab;
	char	**heredoc_res = NULL;

	i = 0;
	size = 0;
	while(i <= d_exe->nb_probable_of_heredocs)
	{
		if(d_exe->heredoc[i] != NULL)
			size++;
		i++;
	}
	i = 0;
	d_exe->nb_of_valid_heredoc = size;
	if (d_exe->nb_of_valid_heredoc == 0)
		return (1);
	//fprintf(stderr, ">> nb of valid heredoc: %d\n", size);
	d_exe->str_heredoc = create_str_heredoc(d_exe->heredoc, d_exe);
	// fprintf(stderr, "str_heredoc : %s\n", d_exe->str_heredoc);
	//fprintf(stderr, "ft_handle_heredoc %s\n", d_exe->str_heredoc);
	heredoc_tab = ft_split_exec(d_exe->str_heredoc, ' ', 0);
    size = ft_tabsize(heredoc_tab);//size_tab = ft_tabsize(d_exe->heredoc);
	// fprintf(stderr, "i debut: %d\n", i);
    while(heredoc_tab[i])
    {
		if (buffer)
		{
        	if (ft_strncmp(buffer, heredoc_tab[i], (ft_strlen(heredoc_tab[i]) + 1)) == 0)
           		i++;
			buffer = NULL;
		}
        if (i == size - 1)
		{
			// fprintf(stderr, "i : %d, size : %d, to check: %s\n", i, size, heredoc_tab[i]);
            heredoc_res = heredoc_data_saved(heredoc_tab[i], d_exe, buffer);
			break;
		}
        buffer = readline("> ");
    }
	//free(buffer)
	i = convert_tab_to_fd_heredoc(heredoc_res);
	return (i); // A CHANGER, VOID FT
}

// void	display_lst_heredoc(t_list **ptr_to_head, char *name)
// {
// 	t_list	*current_node;
// 	int		count;

// 	current_node = *ptr_to_head;
// 	count = 0;
// 	printf("\n%s :\n", name);
// 	if (*ptr_to_head != NULL)
// 	{
// 		while (current_node->next != NULL)
// 		{
// 			printf("Index = %d : ", count);
// 			display_node_heredoc(current_node);
// 			current_node = current_node->next;
// 			count++;
// 		}
// 		printf("Index = %d : ", count);
// 		display_node_heredoc(current_node);
// 	}
// 	else
// 		printf("The stack is empty.\n");
// 	printf("\n");
// }

// void	display_node_heredoc(t_list *lst)
// {
// 	if (lst != NULL)
// 	{
// 		printf("[%p] {value = %s | nx = %p}\n", lst,
// 			lst->valeur,
// 			lst->next);
// 	}
// }
