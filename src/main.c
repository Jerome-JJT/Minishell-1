#include "../minishell.h"

int g_errno = 0;

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
	init_shell(&info_parse, &info_exec, envp); // --->>  Initialisation général
	if (ac == 1) // Sans arg = version minishell
	{
		// set_signals();
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
				print_parsing(&info_exec, "Test");
				// print_token(&info_parse.token, "Test");
				shell_execution(&info_exec, envp, &info_parse);
				tok_clearlst(&info_parse.token);
				reset_shelltab(&info_exec, &info_parse);
			}
		}
	}
	else // avec arg = version Debbug
	{
		// buffer = av[1];
		test[0] = "export \"z=a b c\"";
		test[1] = "export";
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
