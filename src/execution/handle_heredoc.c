#include "minishell.h"

// void heredoc_signals(int num);
// void set_heredoc_signals();

void handle_heredoc(t_exec *d_exe)
{
    int		i;
   	int		size;
    char	*buffer = NULL;
	char	**heredoc_tab;
	char	**heredoc_res = NULL;

	i = 0;
	d_exe->nb_of_valid_heredoc = number_of_valid_heredoc(d_exe);
	if (d_exe->nb_of_valid_heredoc == 0)
		return;
	d_exe->str_heredoc = create_str_heredoc(d_exe->heredoc, d_exe);
	heredoc_tab = ft_split_exec(d_exe->str_heredoc, ' ', 0);
    size = ft_tabsize(heredoc_tab);
    while(heredoc_tab[i])
    {
		//set_heredoc_signals();
		if (buffer)
		{
        	if (ft_strncmp(buffer, heredoc_tab[i], (ft_strlen(heredoc_tab[i]) + 1)) == 0)
           		i++;
			buffer = NULL;
		}
        if (i == size - 1)
		{
            heredoc_res = heredoc_data_saved(heredoc_tab[i], d_exe, buffer);
			break;
		}
        buffer = readline("> ");
    }
	//free(buffer)
	convert_tab_to_fd_heredoc(heredoc_res);
}

// void set_heredoc_signals()
// {
//     struct sigaction sa;

//     sa.sa_flags = 0;
//     sigemptyset(&sa.sa_mask);
//     sa.sa_handler = heredoc_signals;

//     sigaction(SIGQUIT, &sa, NULL); // ctrl backslash
//     sigaction(SIGINT, &sa, NULL); // ctrl c
//     //sigaction(EOF, &sa, NULL); // ctrl d
// }

// void heredoc_signals(int num)
// {
// 	if (num == SIGINT)
// 	{
// 		//return;
// 	}
// 	if (num == SIGQUIT)
// 	{
// 		//kill(SIGKILL, 0);
// 	}
// }
