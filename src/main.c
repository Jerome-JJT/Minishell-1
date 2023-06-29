#include "../minishell.h"

int g_errno = 0;
// int	main(int ac, char **av, char **envp)
// {

//  	(void) ac;
//  	(void) av;
//  	t_shell infos;
// 	//int i = 0;

//  	t_exec	*info_exec = NULL;
// 	info_exec = &(t_exec){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// 	/*------------------VARIABLES_TEST--------------------*/
// 	char *test_tab_cmd[] = {"echo bla", "cat -e", NULL};
// 	char *test_last_out_app[] = {NULL, NULL, NULL}; // essayer avec NULL unique
// 	char *redirections_infile[] = {"text_c.txt text_a.txt", "text_a.txt text_c.txt", NULL};	//"text_a.txt", "text_b.txt"
// 	char *redirections_outfile[] = {"out1 out2", NULL, NULL};
// 	char *redirections_heredoc[] = {NULL, NULL, NULL}; //	mettre NULL si rien et non "" /!|
// 	/*---------------------------------------------------*/

// 	info_exec->number_of_pipes = 1;
// 	info_exec->tab_cmd = test_tab_cmd;

// 	info_exec->env_cpy = envp;
// 	info_exec->redi_infile = redirections_infile;
// 	info_exec->redi_outfile = redirections_outfile;
// 	info_exec->heredoc = redirections_heredoc;
// 	info_exec->append = test_last_out_app;
// 	info_exec->idx = 0;

//  	shell_execution(info_exec, envp, &infos);
// 	//infos.status = shell_execution(infos.arg, info);
// }

/* -------------------- Main principale ----------------------------*/
int	main(int ac, char **av, char **envp)
{
	int			check;
	t_shell		info_parse;
	t_exec		info_exec;
	char		*buffer;

	init_shell(&info_parse, &info_exec, envp); // --->>  Initialisation général
	if (ac == 1) // Sans arg = version minishell
	{

		(void) av;
		while (1)
		{
			//signal(SIGINT, handle_signals); // ctrl c
			//signal(SIGQUIT, handle_signals); // ctrl /
			rl_on_new_line();
			buffer = readline(""GREEN"$>"RESET" ");
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
				print_parsing(&info_exec, "\nBefore exec\n");
				shell_execution(&info_exec, envp, &info_parse);
				tok_clearlst(&info_parse.token);
				reset_exectab(&info_exec);
			}
		}
	}
	else // avec arg = version Debbug
	{
		// buffer = av[1];
		buffer = "<1 cat -e >1| <1 cat -e >2 | <2 wc -c >3";
		check = parse_shell (buffer, &info_parse, &info_exec);
		if (check == 1)
			printf(""RED"Erreur"RESET": nombre quote invalide\n");
		else if (check == 2)
			tok_clearlst(&info_parse.token);
		else
		{
			print_parsing(&info_exec, "\nBefore exec\n");
			shell_execution(&info_exec, envp, &info_parse);
			tok_clearlst(&info_parse.token);
			reset_exectab(&info_exec);
		}
	}
	return (0); 
}
