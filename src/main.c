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

/* -------------------- 1.Check validity parsing ----------------------------*/
static void	ft_check(int check, t_shell *parse, t_exec *exec, char **envp)
{
	if (check == 1)
	{
		printf(""RED"Erreur"RESET": nombre quote invalide\n");
		tok_clearlst(&parse->token);
	}
	else if (check == 2)
		tok_clearlst(&parse->token);
	else if (check == 0)
	{
		shell_execution(exec, envp, parse);
		tok_clearlst(&parse->token);
		reset_shelltab(exec);
	}
}

/* -------------------- 2.Main principale ----------------------------*/
int	main(int ac, char **av, char **envp)
{
	int			check;
	t_shell		info_parse;
	t_exec		info_exec;
	char		*buffer;

	(void) av;
	(void) ac;
	init_shell(&info_parse, &info_exec, envp);
	set_signals();
	while (1)
	{
		rl_on_new_line();
		buffer = readline(""GREEN"$>"RESET" ");
		if (!buffer) 
			exit(0);
		if (*buffer)
			buffer = ft_strtrim(buffer, " ", &info_parse.trash_lst);
		if (buffer && *buffer)
			add_history(buffer);
		check = parse_shell (buffer, &info_parse, &info_exec);
		ft_check(check, &info_parse, &info_exec, envp);
		// Possible leaks ici si buffer non free !
	}
	ft_dlst_clear(&info_parse.trash_lst, free);
	free(info_parse.env);
	return (0);
}
