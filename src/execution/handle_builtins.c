#include "minishell.h"



void		builtins_0(t_pipe *d_pip, t_exec *d_exe, t_shell *d_shell, char *cmd)
{
    (void)cmd;
	int		fork_pid;
   // fprintf(stderr, "builtin_0: %s\n", cmd);
	fork_pid = fork();
	if (fork_pid == -1)
		fprintf(stderr, "fork errot\n"); //perror_msg();
	if (fork_pid == 0)
	{
		close_pipes(d_pip, 1);
		create_cmd_n_args_builtins(d_exe);//d_exe->cmd_n_arg = ft_split_exec(cmd, ' ', 0);
		handle_redirections(d_exe, d_pip);
		if (d_exe->cmd_number == 0)
		{
			first_cmd(d_pip, d_exe);
		}
		else if (d_exe->cmd_number == d_exe->number_of_pipes)
		{
			last_cmd(d_pip, 0, d_exe);
		}
		else
		{
			middle_cmd(d_pip, d_exe, 0);
		}
        builtins_exec(d_exe->cmd_n_arg[0], d_shell, d_exe->cmd_n_arg, d_exe);
		exit(1);
	}
		close_pipes(d_pip, 3);
		pipe(d_pip->fd_pipe1);
}

void	builtins_1(t_pipe *d, t_exec *d_exe, t_shell *d_shell, char *cmd)
{
    (void)cmd;
	int		fork_pid;

	//fprintf(stderr, "builtin_1: %s\n", cmd);
	fork_pid = fork();
	if (fork_pid == -1)
		fprintf(stderr, "fork errot\n"); //perror_msg();
	if (fork_pid == 0)
	{
		close_pipes(d, 2);
		create_cmd_n_args_builtins(d_exe);//d_exe->cmd_n_arg = ft_split_exec(cmd, ' ', 0);
		handle_redirections(d_exe, d);
		if (d_exe->cmd_number == d_exe->number_of_pipes)
		{
			last_cmd(d, 1, d_exe);
		}
		else
		{
			middle_cmd(d, d_exe, 1);
		}
        builtins_exec(d_exe->cmd_n_arg[0], d_shell, d_exe->cmd_n_arg, d_exe);
		exit(1);
	}
	close_pipes(d, 4);
	pipe(d->fd_pipe2);
}

void create_cmd_n_args_builtins(t_exec *exe)
{
	char *arg;
	//int i = 0;
	char **name;

	name = ft_split_exec((exe->tab_cmd[0]), ' ', 0);
	//fprintf(stderr, "name : %s\n", name[0]);
	exe->cmd_n_arg = ft_calloc(3, sizeof(char**));
	exe->cmd_n_arg[0] = ft_calloc(ft_strlen(name[0] + 1), sizeof(char *));
	arg = ft_calloc((ft_strlen(exe->tab_cmd[0]) + (ft_strlen(name[0] + 1))), sizeof(char*));
	//exe->cmd_n_arg[0] = my_malloc(5, sizeof(char*), exe->trash_lst_exe);
	//exe->cmd_n_arg = my_malloc(3,sizeof(char**),exe->trash_lst_exe);
	if(ft_strncmp("echo", name[0], 5) == 0)
	{
		exe->cmd_n_arg[0] = "echo";
	}
	else if(ft_strncmp("cd", name[0], 3) == 0)
	{
		exe->cmd_n_arg[0] = "cd";
	}
	else if(ft_strncmp("env", name[0], 5) == 0)
	{
		exe->cmd_n_arg[0] = "env";
	}
	else if(ft_strncmp("exit", name[0], 5) == 0)
	{
		exe->cmd_n_arg[0] = "exit";
	}
	else if(ft_strncmp("export", name[0], 7) == 0)
	{
		exe->cmd_n_arg[0] = "export";
	}
	else if(ft_strncmp("pwd", name[0], 4) == 0)
	{
		exe->cmd_n_arg[0] = "pwd";
	}
	else if(ft_strncmp("unset", name[0], 6) == 0)
	{
		exe->cmd_n_arg[0] = "unset";
	}
	else
	{
		command_not_found(exe->tab_cmd[0]);
		exit(g_errno);
	}
	arg = ft_strcpy(arg, exe->tab_cmd[0] + (ft_strlen(name[0]) + 1));
	exe->cmd_n_arg[1] = ft_calloc((ft_strlen(arg)), sizeof(char *));
	exe->cmd_n_arg[1] = arg;
	exe->cmd_n_arg[2]= NULL;
	// while(exe->cmd_n_arg[i])
	// {
	// 	fprintf(stderr, "cmd_n_arg_builtins[%d]: %s\n", i, exe->cmd_n_arg[i]);
	// 	i++;
	// }
}