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
		d_exe->cmd_n_arg = ft_split_exec(cmd, ' ', 0);
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
		d_exe->cmd_n_arg = ft_split_exec(cmd, ' ', 0);
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