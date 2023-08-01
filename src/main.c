#include "../minishell.h"

int g_errno = 0;
// int	main(int ac, char **av, char **envp)
// {

//  	(void) ac;
//  	(void) av;
//  	t_shell infos;
// 	//int i = 0;

// 	//t_info info_exec;


//  	t_exec	*info_exec = NULL;
// 	info_exec  = ft_calloc(sizeof(t_exec), 1);
// 	// info_exec = &(t_exec){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// 	/*------------------VARIABLES_TEST--------------------*/
// 	char *test_tab_cmd[] = {"pwd", NULL};
// 	char *redirections_infile[] = {NULL, NULL};	//"text_a.txt", "text_b.txt"
// 	char *redirections_outfile[] = {NULL, NULL};
// 	char *redirections_heredoc[] = {NULL, NULL}; //	mettre NULL si rien et non "" /!|
// 	/*---------------------------------------------------*/

// 	info_exec->number_of_pipes = 0;
// 	info_exec->tab_cmd = test_tab_cmd;

// 	info_exec->env_cpy = envp;
// 	info_exec->redi_infile = redirections_infile;
// 	info_exec->redi_outfile = redirections_outfile;
// 	info_exec->heredoc = redirections_heredoc;
// 	info_exec->idx = 0;

//  	shell_execution(info_exec, envp, &infos);
// 	//infos.status = shell_execution(infos.arg, info);
// }

/* -------------------- Main principale ----------------------------*/
int	main(int ac, char **av, char **envp)
{
	int			check;
	int			i;
	t_shell		info_parse;
	t_exec		info_exec;
	char		*buffer;
	char		*test[10];

	i = 0;
	init_shell(&info_parse, &info_exec, envp);
	if (ac == 1) // Sans arg = version minishell
	{
		set_signals();
		(void) av;
		while (1)
		{
			rl_on_new_line();
				add_history("<<a <<b <<c");
			buffer = readline(""GREEN"$>"RESET" ");
			if (buffer && *buffer)
				add_history(buffer);
			rl_redisplay();
			check = parse_shell (buffer, &info_parse, &info_exec);
			if (check == 1)
			{
				printf(""RED"Erreur"RESET": nombre quote invalide\n");
				tok_clearlst(&info_parse.token);
			}
			else if (check == 2)
				tok_clearlst(&info_parse.token);
			else if (check == 0)
			{
				// print_parsing(&info_exec, "Test");
				// print_token(&info_parse.token, "Test");
				shell_execution(&info_exec, envp, &info_parse);
				tok_clearlst(&info_parse.token);
				reset_shelltab(&info_exec, &info_parse);
				free(buffer);
			}
		}
		ft_dlst_clear(&info_parse.trash_lst, free);
	}
	else // avec arg = version Debbug
	{
		test[0] = "echo \"'$USER$USER'\"";
		test[1] = NULL;
		test[2] = NULL;
		test[3] = NULL;
		test[4] = NULL;
		while (test[i])
		{
			check = parse_shell (test[i], &info_parse, &info_exec);
			if (check == 1)
				printf(""RED"Erreur"RESET": nombre quote invalide\n");
			else if (check == 2)
				tok_clearlst(&info_parse.token);
			else
			{
				print_parsing(&info_exec, "Test");
				shell_execution(&info_exec, envp, &info_parse);
				tok_clearlst(&info_parse.token);
				reset_shelltab(&info_exec, &info_parse);
			}
			i++;
		}
	}
	return (0);
}
