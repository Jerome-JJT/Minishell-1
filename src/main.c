#include "../minishell.h"

int g_errno = 0;
// int	main(int ac, char **av, char **envp)
// {

// 	(void) ac;
// 	(void) av;
// 	t_shell infos;

// 	t_exec	*info_exec = NULL;
// 	info_exec = &(t_exec){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// 	/*------------------VARIABLES_TEST--------------------*/
// 	char *test_tab_cmd[] = {"cat -e", NULL};
// 	char *test_cmd_simple[] = {"wc", "-l", NULL};
// 	char *redirections_infile[] = {NULL};	//"text_a.txt", "text_b.txt"
// 	char *redirections_outfile[] = {NULL};
// 	char *redirections_heredoc[] = {"begin", "middle", "end"};
// 	/*---------------------------------------------------*/

// 	info_exec->number_of_pipes = 0;
// 	info_exec->tab_cmd = test_tab_cmd;
// 	info_exec->cmd_n_arg = test_cmd_simple;

// 	info_exec->env_cpy = envp;
// 	info_exec->redi_infile = redirections_infile;
// 	info_exec->redi_outfile = redirections_outfile;
// 	info_exec->heredoc = redirections_heredoc;

	// shell_execution(info_exec, envp, &infos);
	// infos.status = shell_execution(info.arg, info);
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
				print_parsing(&info_exec, "Before exec");
				shell_execution(&info_exec, envp, &info_parse);
				tok_clearlst(&info_parse.token);
				ft_tabreset(info_exec.tab_cmd);
			}
		}
	}
	else // avec arg = version Debbug
	{
		// buffer = av[1];
		buffer = "salut";
		check = parse_shell (buffer, &info_parse, &info_exec);
		if (check == 1)
			printf(""RED"Erreur"RESET": nombre quote invalide\n");
		else if (check == 2)
			tok_clearlst(&info_parse.token);
		else
		{
			print_parsing(&info_exec, "Before exec");
			shell_execution(&info_exec, envp, &info_parse);
			tok_clearlst(&info_parse.token);
		}
	}
	return (0); 
}
