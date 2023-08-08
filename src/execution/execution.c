#include "minishell.h"

void update_env(t_exec *exe, t_shell *info);

int shell_execution(t_exec *d_exec, char **env, t_shell *shell_info)
{
	(void)shell_info;
	(void) env;
	int i;
	t_pipe	d_pip;
	// d_pip = (t_pipe){0};
	ft_bzero(&d_pip, sizeof(t_pipe));
	/*------------------VARIABLES_TEST--------------------*/

	//char *builtins[] = {"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};
	/*---------------------------------------------------*/
	//d_exec->tab_cmd[0] = NULL;
	fprintf(stderr, "check value tab_cmd[0]: %s\n", d_exec->tab_cmd[0]);
	fprintf(stderr, "check value tab_cmd[1]: %s\n", d_exec->tab_cmd[1]);
	fprintf(stderr, "check value tab_cmd[2]: %s\n", d_exec->tab_cmd[2]);
	//fprintf(stderr, "check value redi_in[0]: %s\n", d_exec->redi_infile[0]);
	// fprintf(stderr, "check value redi_in[2]: %s\n", d_exec->redi_infile[2]);
	//fprintf(stderr, "check value redi_out0: %s\n", d_exec->redi_outfile[0]);
	// fprintf(stderr, "check value redi_out1: %s\n", d_exec->redi_outfile[1]);
	// fprintf(stderr, "check value redi_out2: %s\n", d_exec->redi_outfile[2]);
	//fprintf(stderr, "check value heredoc[0]: %s\n", d_exec->heredoc[0]);
	//fprintf(stderr, "check value apppend0: %s\n", d_exec->append[0]);
	//fprintf(stderr, "check value apppend1: %s\n", d_exec->append[1]);
	// fprintf(stderr, "check value apppend2: %s\n", d_exec->append[2]);
	//fprintf(stderr, "nb de pipe0: %d\n", d_exec->number_of_pipes);
	i = 0;
	while (d_exec->tab_cmd[i])
		i++;
	//d_exec->nb_probable_of_heredocs = i;
	d_exec->nb_probable_of_heredocs = d_exec->number_of_pipes + 1;
	//fprintf(stderr, "nb probable heredoc: % d\n", d_exec->nb_probable_of_heredocs);
	//d_exec->number_of_pipes = i - 1;
	//fprintf(stderr, "nb de pipe1: %d\n", d_exec->number_of_pipes);
	d_exec->last_append = NULL;
	handle_heredoc(d_exec);
	handle_pipes(&d_pip.fd_pipe1, &d_pip.fd_pipe2);
	signals_update();
	// if (!d_exec->tab_cmd)
	// 	exit(0);
	if(d_exec->number_of_pipes == 0)
	{
		//fprintf(stderr, "exec no pipe begin\n");
		execution_no_pipe(d_exec, &d_pip, shell_info);
	}
	if (d_exec->number_of_pipes > 0)
	{
		i = execution_with_pipes(d_exec, &d_pip, shell_info);
	}
	d_exec->cmd_number = 0;
	d_exec->idx = 0;
	while (i-- > 0)
		wait(NULL);
	//fprintf(stderr, "checkdsd\n");
	return (0);
}

int execution_with_pipes(t_exec *d_exec, t_pipe *d_pip, t_shell *shell_info)
{
	int i;
	char *builtins[] = {"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};

	i = 0;
	while (i <= d_exec->number_of_pipes)
	{
		if (d_exec->tab_cmd[i])
		{
			if(is_builtins(d_exec->tab_cmd[i], builtins) == 1)
			{
				if (i % 2 == 0)
				{
					// fprintf(stderr, ">> builtins_0 = %s, idx : %d\n", d_exec->tab_cmd[i], d_exec->idx);
					builtins_0(d_pip, d_exec, shell_info, d_exec->tab_cmd[i]);
				}
				else
				{
					// fprintf(stderr, ">> builtins_1 = %s\n", d_exec->tab_cmd[i]);
					builtins_1(d_pip, d_exec, shell_info, d_exec->tab_cmd[i]);
				}
			}
			if(is_builtins(d_exec->tab_cmd[i], builtins) == 0)
			{
				if (i % 2 == 0)
				{
					// fprintf(stderr, ">> process_0 = %s, idx : %d\n", d_exec->tab_cmd[i], d_exec->idx);
					child_process_0(d_pip, d_exec, shell_info, d_exec->tab_cmd[i]);
				}
				else
				{
					// fprintf(stderr, ">> process_1 = %s\n", d_exec->tab_cmd[i]);
					child_process_1(d_pip, d_exec, shell_info, d_exec->tab_cmd[i]);
				}
			}
		}
		i++;
		d_exec->idx++;
		d_exec->cmd_number++;
	}
	return (i);
}

void execution_no_pipe(t_exec *d_exec, t_pipe *d_pip, t_shell *shell_info)
{
	char *builtins[8];
	int out_backup;

	builtins[0] = "cd";
	builtins[1] = "echo";
	builtins[2] = "env";
	builtins[3] = "exit";
	builtins[4] = "export";
	builtins[5] = "pwd";
	builtins[6] = "unset";
	builtins[7] = NULL;
	if (d_exec->tab_cmd[0])
	{
		if(is_builtins(d_exec->tab_cmd[0], builtins) == 1)
		{
			//fprintf(stderr, "pipe = 0, builtins\n");
			out_backup = dup(1);
			if (out_backup == -1)
				perror_msg_system(5);
			handle_dup_fd_single_cmd(d_pip, d_exec);
			create_cmd_n_args_builtins(d_exec);
			builtins_exec(d_exec->cmd_n_arg[0], shell_info, d_exec->cmd_n_arg, d_exec);
			dup2(out_backup, 1);
			if (out_backup == -1)
				perror_msg_system(4);
			return;
		}
		else
		{
			// fprintf(stderr, "else\n");
			handle_single_cmd(d_pip, d_exec, shell_info, d_exec->tab_cmd[0]);
		}
	}
}

void builtins_exec(char *builtins_name, t_shell *info, char **cmd, t_exec *exe)
{
	int i;
	i = 0;
	info->arg = cmd;
	if(ft_strncmp("echo", builtins_name, ft_strlen(builtins_name)) == 0)
		echo_minishell(*(exe->cmd_n_arg + 1), &info->trash_lst);
	if(ft_strncmp("cd", builtins_name, ft_strlen(builtins_name)) == 0)
	{
		//fprintf(stderr, "built_cd_minishell\n");
		cd_minishell(info, *(exe->cmd_n_arg + 1));
	}
	if(ft_strncmp("env", builtins_name, ft_strlen(builtins_name)) == 0)
		env_minishell(info, *(exe->cmd_n_arg + 1));
	if(ft_strncmp("exit", builtins_name, ft_strlen(builtins_name)) == 0)
	{
		exit_minishell(exe->cmd_n_arg + 1, &info->trash_lst);
		//fprintf(stderr, "exit_minishell\n");
	}
	if(ft_strncmp("export", builtins_name, ft_strlen(builtins_name)) == 0)
	{
		//fprintf(stderr, "built_export_minishell0\n");
		export_minishell(info, exe->cmd_n_arg + 1);
		i = 1;
		//fprintf(stderr, "built_export_minishell1\n");
	}
	if(ft_strncmp("pwd", builtins_name, ft_strlen(builtins_name)) == 0)
		pwd_minishell(info);
	if(ft_strncmp("unset", builtins_name, ft_strlen(builtins_name)) == 0)
	{
		unset_minishell(info, exe->cmd_n_arg + 1);
		i = 1;
		//fprintf(stderr, "built_unset_minishell\n");
	}
	if (i == 1)
		update_env(exe, info);
}

void update_env(t_exec *exe, t_shell *info)
{
	exe->env_cpy = lst_to_tab(info->env, exe->trash_lst_exe);
}

int is_builtins(char *cmd_to_compare, char** builtins_list)
{
	int i;

	i = 0;
	while(builtins_list[i])
	{
		if(ft_strncmp(cmd_to_compare, builtins_list[i], ft_strlen(builtins_list[i])) == 0)
			return(1);
		i++;
	}
	return (0);
}
