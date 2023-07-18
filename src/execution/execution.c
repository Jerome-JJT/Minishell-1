#include "minishell.h"

int shell_execution(t_exec *d_exec, char **env, t_shell *shell_info)
{
	(void)shell_info;
	(void) env;
	int i;
	t_pipe	d_pip;
	d_pip = (t_pipe){0};
	/*------------------VARIABLES_TEST--------------------*/
	
	char *builtins[] = {"cd", "echo", "env", "exit", "export", "pwd", "unset", NULL};
	/*---------------------------------------------------*/
	// fprintf(stderr, "check value tab_cmd: %s\n", d_exec->tab_cmd[0]);
	fprintf(stderr, "check value redi_in[0]: %s\n", d_exec->redi_infile[0]);
	//fprintf(stderr, "check value redi_in[2]: %s\n", d_exec->redi_infile[2]);
	fprintf(stderr, "check value redi_out: %s\n", d_exec->redi_outfile[0]);
	//fprintf(stderr, "check value heredoc[0]: %s\n", d_exec->heredoc[0]);
	fprintf(stderr, "check value apppend: %s\n", d_exec->append[0]);
	i = 0;
	// while (d_exec->heredoc[i])
	// {
	// 	fprintf(stderr, "check value heredoc: %s\n", d_exec->heredoc[i]);
	// 	i++;
	// }
	// fprintf(stderr, "check value heredoc: %s\n", d_exec->heredoc[i]);
	// i = 0;
	while (d_exec->tab_cmd[i])
		i++;
	d_exec->nb_probable_of_heredocs = i;
	d_exec->number_of_pipes = i - 1;
	d_exec->last_append = NULL;
	handle_heredoc(d_exec);
	//pre_handle_append(d_exec);
	handle_pipes(&d_pip.fd_pipe1, &d_pip.fd_pipe2);
	i = 0;
	if (!d_exec->tab_cmd)
		exit(0);
	if(d_exec->number_of_pipes == 0)
	{
		if(is_builtins(d_exec->tab_cmd[i], builtins) == 1)
		{	
			//fprintf(stderr, "pipe = 0, builtins\n");
			handle_dup_fd_single_cmd(&d_pip, d_exec);
			// handle_dup_single_cmd(&d_pip);
			d_exec->cmd_n_arg = ft_split_exec(d_exec->tab_cmd[i], ' ', 0);
			builtins_exec(d_exec->cmd_n_arg[0], shell_info, d_exec->cmd_n_arg, d_exec);
			return (0);
		}
		else
			handle_single_cmd(&d_pip, d_exec, shell_info, d_exec->tab_cmd[i]);
	}
	if (d_exec->number_of_pipes > 0)
	{
		while (i <= d_exec->number_of_pipes)
		{
			if(is_builtins(d_exec->tab_cmd[i], builtins) == 1)
			{
				if (i % 2 == 0)
				{
					//fprintf(stderr, ">> builtins_0 = %s, idx : %d\n", d_exec->tab_cmd[i], d_exec->idx);
					builtins_0(&d_pip, d_exec, shell_info, d_exec->tab_cmd[i]);
				}
				else
				{
					//fprintf(stderr, ">> builtins_1 = %s\n", d_exec->tab_cmd[i]);
					builtins_1(&d_pip, d_exec, shell_info, d_exec->tab_cmd[i]);
				}
			}
			if(is_builtins(d_exec->tab_cmd[i], builtins) == 0)
			{
				if (i % 2 == 0)
				{
					//fprintf(stderr, ">> process_0 = %s, idx : %d\n", d_exec->tab_cmd[i], d_exec->idx);
					child_process_0(&d_pip, d_exec, shell_info, d_exec->tab_cmd[i]);
				}
				else
				{
					//fprintf(stderr, ">> process_1 = %s\n", d_exec->tab_cmd[i]);
					child_process_1(&d_pip, d_exec, shell_info, d_exec->tab_cmd[i]);
				}
			}
			i++;
			d_exec->idx++;
			//fprintf(stderr, "cmd_number:%d\n", d_exec->cmd_number);
			d_exec->cmd_number++;
			//wait (NULL);
		}
	}
	//d_exec->reset_exec_tab = d_exec->idx;
	//fprintf(stderr, "rest_exec_tab:%d\n", d_exec->reset_exec_tab);
	d_exec->cmd_number = 0;
	d_exec->idx = 0;
	//d_exec->heredoc = NULL; // provoque des Segmentation fault (core dumped)
	// i = 0;
	// while(d_exec->heredoc[i])
	// {
	// 	fprintf(stderr, "fin exe->heredoc[%d]: %s\n", i, d_exec->heredoc[i]);
	// 	i++;
	// }
	//fprintf(stderr, "finito\n");
	while (i-- > 0)
		wait(NULL);
	return (0);
}

void builtins_exec(char *builtins_name, t_shell *info, char **cmd, t_exec *exe)
{
	info->arg = cmd;
	if(ft_strncmp("echo", builtins_name, ft_strlen(builtins_name)) == 0)
	{
		echo_minishell(exe->cmd_n_arg + 1);
		//fprintf(stderr, "built_echo\n");
	}
	if(ft_strncmp("cd", builtins_name, ft_strlen(builtins_name)) == 0)
	{
		//fprintf(stderr, "built_cd_minishell\n");
		cd_minishell(info, *(exe->cmd_n_arg + 1));
	}
	if(ft_strncmp("env", builtins_name, ft_strlen(builtins_name)) == 0)
	{
		//fprintf(stderr, "built_env_minishell\n");
		env_minishell(info, *(exe->cmd_n_arg + 1));
	}
	if(ft_strncmp("exit", builtins_name, ft_strlen(builtins_name)) == 0)
	{
		exit_minishell(exe->cmd_n_arg + 1, &info->trash_lst);
		//fprintf(stderr, "exit_minishell\n");
	}
	if(ft_strncmp("export", builtins_name, ft_strlen(builtins_name)) == 0)
	{
		export_minishell(info, exe->cmd_n_arg + 1);
		//fprintf(stderr, "built_export_minishell\n");
	}
	if(ft_strncmp("pwd", builtins_name, ft_strlen(builtins_name)) == 0)
	{
		pwd_minishell(info);
		//fprintf(stderr, "built_pwd_minishell\n");
	}
	if(ft_strncmp("unset", builtins_name, ft_strlen(builtins_name)) == 0)
	{
		unset_minishell(info, exe->cmd_n_arg + 1);
		//fprintf(stderr, "built_unset_minishell\n");
	}
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
