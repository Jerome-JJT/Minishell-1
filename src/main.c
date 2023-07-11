#include "../minishell.h"

int g_errno = 0;
// int	main(int ac, char **av, char **envp)
// {

//  	(void) ac;
//  	(void) av;
//  	t_shell infos;
// 	int i = 0;

//  	t_exec	*info_exec = NULL;
// 	info_exec = &(t_exec){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// 	/*------------------VARIABLES_TEST--------------------*/

// 	/*--------------------cmd testing---------------------*/

// 	char *test_tab_cmd[] = {"ls -l", NULL};								// 1cmd NB
// 	char *test_tab_cmd[] = {"pwd", NULL};							// 1 cmd B

// 	char *test_tab_cmd[] = {"ls -l", "cat -e", NULL};						// 2 cmd NB
// 	char *test_tab_cmd[] = {"echo bla", "pwd", NULL};						// 2 cmd B
// 	char *test_tab_cmd[] = {"echo coucou", "echo salut", NULL};					// 2 cmd NB/B

// 	char *test_tab_cmd[] = {"cat -e", "cat -e", "cat -e", NULL};			// 3 cmd NB
// 	char *test_tab_cmd[] = {"echo bla", "pwd", "echo salut", NULL};		// 3 cmd B
// 	char *test_tab_cmd[] = {"cat -e", "echo bla", "cat -e", NULL};		// 3 cmd NB/B/NB
// 	char *test_tab_cmd[] = {"pwd", "cat -e", "echo coucou", NULL};		// 3 cmd B/NB/B

// 	char *test_tab_cmd[] = {"cat -e", "echo bla", "echo coucou", "pwd", NULL};		// 3 cmd B/NB/B
// 	/*---------------------infiles testing------------------*/
// 	/*-- 1 cmd --*/
// 	char *redi_in[] = {NULL, NULL};										// 1 cmd, no in
// 	char *redi_in[] = {"tx_c.txt", NULL};									// 1 cmd, 1 in
// 	char *redi_in[] = {"tx_c.txt tx_a.txt", NULL};						// 1 cmd, 2 in

// 	/*-- 2 cmd --*/
// 	char *redi_in[] = {NULL, NULL, NULL};									// 2 cmd,  no in
// 	char *redi_in[] = {NULL, "tx_a.txt", NULL};							// 2 cmd,  1 in, NULL
// 	char *redi_in[] = {"tx_c.txt", "tx_a.txt", NULL};						// 2 cmd,  1 in
// 	char *redi_in[] = {"tx_c.txt tx_a.txt", "tx_a.txt tx_c.txt", NULL};	// 2 cmd, 2 in
// 	char *redi_in[] = {NULL, "tx_a.txt tx_c.txt", NULL};					// 2 cmd, 2 in, NULL

// 	/*-- 3 cmd --*/
// 	char *redi_in[] = {NULL, NULL, NULL, NULL};							// 3 cmd, 1 in, no in
// 	char *redi_in[] = {"tx_c.txt", NULL, "tx_b.txt", NULL};				// 3 cmd, 1 in, NULL
// 	char *redi_in[] = {"tx_c.txt", "tx_a.txt ", "tx_b.txt", NULL};		// 3 cmd, 1 in
// 	char *redi_in[] = {"tx_c.txt tx_a.txt", "tx_a.txt tx_c.txt", "tx_a.txt tx_b.txt", NULL};	// 3 cmd, 2 in
// 	char *redi_in[] = {NULL, "tx_a.txt tx_c.txt", "tx_a.txt tx_b.txt", NULL};	// 3 cmd, 2 in, NULL

// 	char *redi_in[] = {"tx_c.txt", NULL, NULL, NULL, NULL};							// 3 cmd, 1 in, no in
// 	/*---------------------outfiles testing-----------------*/
// 	/*-- 1 cmd --*/
// 	char *redi_out[] = {NULL, NULL};											// 1 cmd, no out
// 	char *redi_out[] = {"out1", NULL};									// 1 cmd, 1 out
// 	char *redi_out[] = {"out1 out2", NULL};								// 1 cmd, 2 out

// 	/*-- 2 cmd --*/
// 	char *redi_out[] = {NULL, NULL, NULL};								// 2 cmd, no out
// 	char *redi_out[] = {NULL, "out2", NULL};								//2 cmd, 1 out, NULL
// 	char *redi_out[] = {"out1", "out2", NULL};							//2 cmd, 1 out
// 	char *redi_out[] = {"out1", "out1", NULL};							//2 cmd, 1 out, SAME OUT
// 	char *redi_out[] = {"out1 out2", "out3 out4", NULL};					//2 cmd, 2 out
// 	char *redi_out[] = {NULL, "out3 out4", NULL};						//2 cmd, 2 out, NULL
// 	char *redi_out[] = {"out1 out2", "out3 out2", NULL};					//2 cmd, 2 out, SAME OUT

// 	/*-- 3 cmd --*/
// 	char *redi_out[] = {NULL, NULL, NULL, NULL};							// 3 cmd, no out
// 	char *redi_out[] = {"out1", "out2", "out3", NULL};					// 3 cmd, 1 out
// 	char *redi_out[] = {"out1 out2", "out3 out4", "out5 out6", NULL};	// 3 cmd, 2 out
// 	char *redi_out[] = {NULL, "out3 out4", "out5 out6", NULL};			// 3 cmd, 2 out, NULL
// 	char *redi_out[] = {"out1 out2", "out3 out4", "out5 out4", NULL};	// 3 cmd, 2 out, SAME OUT
// 	char *redi_out[] = {NULL, "out3 out4", "out5 out4", NULL};			// 3 cmd, 2 out, SAME OUT, NULL


// 	/*----------------------heredoc testing-------------------*/
// 	/*-- 1 cmd --*/
// 	char *redi_here[] = {NULL, NULL}; 											//	1 cmd, no heredoc
// 	char *redi_here[] = {"a", NULL}; 										//	1 cmd, 1 here
// 	char *redi_here[] = {"a b c", NULL}; 									//	1 cmd, 3 here

// 	/*-- 2 cmd --*/
// 	char *redi_here[] = {NULL, NULL, NULL}; 								//	2 cmd, no here
// 	char *redi_here[] = {"a", "b", NULL}; 								//	2 cmd, 1 here
// 	char *redi_here[] = {"a b", "c d", NULL}; 							// 2 cmd, 2 here
// 	char *redi_here[] = {NULL, "c d", NULL}; 							//	2 cmd, 2 here, NULL
// 	char *redi_here[] = {"a b", "c b", NULL}; 							// 2 cmd, 2 here, SAME HERE
// 	char *redi_here[] = {NULL, "c d", NULL}; 							//	2 cmd, 2 here, NULL

// 	/*-- 3 cmd --*/
// 	char *redi_here[] = {NULL, NULL, NULL, NULL}; 						//	3 cmd, no here
// 	char *redi_here[] = {"a", "b", "c", NULL}; 							// 3 cmd, 1 here
// 	char *redi_here[] = {"a b", "c d", "e f", NULL}; 					//	3 cmd, 2 here
// 	char *redi_here[] = {"a b", "c d", "e a", NULL}; 					//	3 cmd, 2 here, SAME HERE
// 	char *redi_here[] = {NULL, "c d", "e f", NULL}; 						//	3 cmd, 2 here, NULL
// 	char *redi_here[] = {NULL, "c d", "e c", NULL}; 						//	3 cmd, 2 here, NULL, SAME HERE

// 	char *redi_here[] = {NULL, NULL, NULL, NULL, NULL}; 						//	3 cmd, no here
// 	/*-------------------append testing---------------------*/
// 	/*-- 1 cmd --*/
// 	char *test_app[] = {NULL, NULL}; 											// 1 cmd, no app
// 	char *redi_out[] = {NULL, NULL};								

// 	char *test_app[] = {"A_app1", NULL}; 									// 1 cmd, 1 app
// 	char *redi_out[] = {NULL, NULL};

// 	char *test_app[] = {"A_app1 A_app2", NULL}; 							// 1 cmd, 2 app
// 	char *redi_out[] = {NULL, NULL};	

// 	char *test_app[] = {"O_out1 A_app1", NULL}; 							// 1 cmd, 2 app
// 	char *redi_out[] = {"out1", NULL};									

// 	/*-- 2 cmd --*/
// 	char *test_app[] = {NULL, NULL, NULL}; 								// 2 cmd, no app
// 	char *redi_out[] = {NULL, NULL, NULL};								

// 	char *test_app[] = {NULL, "A_app2", NULL}; 							// 2 cmd, 1 app, APP, NULL
// 	char *redi_out[] = {NULL, NULL, NULL};							

// 	char *test_app[] = {"A_app1", "A_app2", NULL}; 						// 2 cmd, 1 app, APP
// 	char *redi_out[] = {NULL, NULL, NULL};							

// 	char *test_app[] = {"O_out1", "O_out2", NULL};						// 2 cmd, 1 app, OUT
// 	char *redi_out[] = {"out1", "out2", NULL};							

// 	char *test_app[] = {"O_out1 A_app1", "O_out2 A_app2", NULL}; 		// 2 cmd, 2 app, APP
// 	char *redi_out[] = {"out1", "out2", NULL};						

// 	char *test_app[] = {"O_out1 A_app1", "O_out2 A_app1", NULL}; 		// 2 cmd, 2 app, APP, SAME APP
// 	char *redi_out[] = {"out1", "out2", NULL};						

// 	char *test_app[] = {NULL, "O_out2 A_app2", NULL}; 					// 2 cmd, 2 app, APP, NULL
// 	char *redi_out[] = {NULL, "out2", NULL};						

// 	char *test_app[] = {"O_out1 A_app1", "A_app2 O_out2", NULL}; 		// 2 cmd, 2 app, OUT
// 	char *redi_out[] = {"out1", "out2", NULL};							

// 	char *test_app[] = {"O_out1 A_app1", "A_app2 O_out1", NULL}; 		// 2 cmd, 2 app, OUT, SAME OUT
// 	char *redi_out[] = {"out1", "out1", NULL};						

// 	char *test_app[] = {NULL, "A_app2 O_out2", NULL}; 					// 2 cmd, 2 app, OUT, NULL
// 	char *redi_out[] = {NULL, "out2", NULL};							
	
// 	/*-- 3 cmd --*/
// 	char *test_app[] = {NULL, NULL, NULL, NULL}; 							// 3 cmd, no app
// 	char *redi_out[] = {NULL, NULL, NULL, NULL};							

// 	char *test_app[] = {"O_out1", "O_out2", "O_out3", NULL};				// 3 cmd, 1 app, OUT
// 	char *redi_out[] = {"out1", "out2", "out3", NULL};					

// 	char *test_app[] = {"A_app1", "A_app2", "App_3", NULL}; 				// 3 cmd, 1 app, APP
// 	char *redi_out[] = {NULL, NULL, NULL, NULL};								
	
// 	char *test_app[] = {NULL, "A_app2", "App_3", NULL}; 					// 3 cmd, 1 app, APP, NULL				// 3 cmd, 1 app, APP
// 	char *redi_out[] = {NULL, NULL, NULL, NULL};								

// 	char *test_app[] = {"O_o1 A_a1", "O_o2 A_a2", "O_o3 A_a3", NULL}; 	// 3 cmd, 2 app, APP
// 	char *redi_out[] = {"o1", "o2", "o3", NULL};				

// 	char *test_app[] = {"O_o1 A_a1", "O_o2 A_a2", "A_a3 O_o3", NULL}; 	// 3 cmd, 2 app, OUT
// 	char *redi_out[] = {"o1", "o2", "o3", NULL};				

// 	char *test_app[] = {NULL, "O_o2 A_a2", "O_o3 A_a3", NULL}; 			// 3 cmd, 2 app, APP, NULL
// 	char *redi_out[] = {NULL, "o2", "o3", NULL};					

// 	char *test_app[] = {NULL, "O_out2 A_app2", "A_a3 O_o3", NULL}; 		// 3 cmd, 2 app, OUT, NULL
// 	char *redi_out[] = {NULL, "o2", "o3", NULL};				

// 	char *test_app[] = {"O_o1 A_a1", "A_a1 O_o2", "O_o3 A_a2",  NULL}; 	// 3 cmd, 2 app, APP, SAME APP
// 	char *redi_out[] = {"o1", "o2", "o3", NULL};				

// 	char *test_app[] = {"O_o1 A_a1", "A_a2 O_o2", "A_a3 O_o2",  NULL}; 	// 3 cmd, 2 app, APP, SAME OUT
// 	char *redi_out[] = {"o1", "o2", "o2", NULL};				

// 	char *test_app[] = {"O_o1 A_a1", "A_a2 O_o2", "O_o3", NULL}; 		// 3 cmd, 2 app, OUT, no APP LAST
// 	char *redi_out[] = {"o1", "o2", "o3", NULL};		

// 	char *test_app[] = {"A_b O_1", NULL, "O_2 A_z", "O_3 A_c", NULL}; 	// 3 cmd, 2 app, APP, SAME APP
// 	char *redi_out[] = {"1", NULL, "2", "3", NULL};		
// 	/*---------------------------------------------------*/

// 	info_exec->number_of_pipes = 0;
// 	info_exec->tab_cmd = test_tab_cmd;

// 	info_exec->env_cpy = envp;
// 	info_exec->redi_infile = redi_in;
// 	info_exec->redi_outfile = redi_out;
// 	info_exec->heredoc = redi_here;
// 	info_exec->append = test_app;
// 	info_exec->idx = 0;

//  	shell_execution(info_exec, envp, &infos);
// 	infos.status = shell_execution(infos.arg, info);
// }

/* -------------------- Main principale ----------------------------*/
int	main(int ac, char **av, char **envp)
{
	int			check;
	int			i;
	t_shell		info_parse;
	t_exec		info_exec;
	char		*buffer;
	char		*test[3];

	i = 0;
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
				reset_shelltab(&info_exec, &info_parse);
			}
		}
	}
	else // avec arg = version Debbug
	{
		// buffer = av[1];
		test[0] = "export salut hello bonjour";
		test[1] = "export";
		test[2] = NULL;
		while (test[i])
		{
			check = parse_shell (test[i], &info_parse, &info_exec);
			if (check == 1)
				printf(""RED"Erreur"RESET": nombre quote invalide\n");
			else if (check == 2)
				tok_clearlst(&info_parse.token);
			else
			{
				print_parsing(&info_exec, "\nBefore exec\n");
				shell_execution(&info_exec, envp, &info_parse);
				tok_clearlst(&info_parse.token);
				reset_shelltab(&info_exec, &info_parse);
			}
			i++;
		}
	}
	return (0); 
}
