#include "minishell.h"

void		builtins_0(t_pipe *d_pip, t_exec *d_exe, t_shell *d_shell, char *cmd)
{
    (void)cmd;
	int		fork_pid;
   // fprintf(stderr, "builtin_0: %s\n", cmd);
	fork_pid = fork();
	if (fork_pid == -1)
		perror_msg_system(1);//fprintf(stderr, "fork errot\n"); //perror_msg();
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
		if (pipe(d_pip->fd_pipe1) == -1)
			perror_msg_system(2);
}

void	builtins_1(t_pipe *d, t_exec *d_exe, t_shell *d_shell, char *cmd)
{
    (void)cmd;
	int		fork_pid;

	//fprintf(stderr, "builtin_1: %s\n", cmd);
	fork_pid = fork();
	if (fork_pid == -1)
		perror_msg_system(1);//fprintf(stderr, "fork errot\n"); //perror_msg();
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
	if (pipe(d->fd_pipe2) == -1)
		perror_msg_system(2);
}

void create_cmd_n_args_builtins(t_exec *exe)
{
	char *arg;
	//int i = 0;
	char **name;
	size_t size;

	size = ft_strlen(exe->tab_cmd[exe->idx]);
	name = ft_split_exec((exe->tab_cmd[exe->idx]), ' ', 0);
	exe->cmd_n_arg = ft_calloc(3, sizeof(char**));
	exe->cmd_n_arg[0] = ft_calloc(ft_strlen(name[0] + 1), sizeof(char *));
	fill_name_cmd_builtins(exe, name[0]);
	if(ft_strlen(name[0]) < size)
	{
		arg = ft_calloc((ft_strlen(exe->tab_cmd[exe->idx]) + (ft_strlen(name[0] + 1))) + 1, sizeof(char*)); // ajout + 1 \0
		exe->cmd_n_arg[1] = ft_calloc((ft_strlen(arg)) + 1, sizeof(char *)); // ajout +1 , \0
		arg = ft_strcpy(arg, exe->tab_cmd[exe->idx] + (ft_strlen(name[0]) + 1));
		exe->cmd_n_arg[1] = arg;
	}
	// i = 0;
	// while(exe->cmd_n_arg[i])
	// {
	// 	fprintf(stderr, ">>cmd_n_arg_builtins[%d]: %s\n", i, exe->cmd_n_arg[i]);
	// 	i++;
	// }
}

void fill_name_cmd_builtins(t_exec *exe, char *name)
{
	if(ft_strncmp("echo", name, 5) == 0)
		exe->cmd_n_arg[0] = "echo";
	else if(ft_strncmp("cd", name, 3) == 0)
		exe->cmd_n_arg[0] = "cd";
	else if(ft_strncmp("env", name, 4) == 0)
		exe->cmd_n_arg[0] = "env";
	else if(ft_strncmp("exit", name, 5) == 0)
		exe->cmd_n_arg[0] = "exit";
	else if(ft_strncmp("export", name, 7) == 0)
	{
		fprintf(stderr, "arg export\n");
		exe->cmd_n_arg[0] = "export";
	}
	else if(ft_strncmp("pwd", name, 4) == 0)
		exe->cmd_n_arg[0] = "pwd";
	else if(ft_strncmp("unset", name, 6) == 0)
		exe->cmd_n_arg[0] = "unset";
	else
		command_not_found(exe->tab_cmd[exe->idx]);
}
