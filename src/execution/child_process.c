#include "minishell.h"

void prepare_cmd(t_exec *d_exe, t_shell *d_shell, char *cmd);

void handle_single_cmd(t_pipe *d_pip, t_exec *d_exe, t_shell *d_shell, char *cmd)
{
    int fork_pid;
	int status;
    //fprintf(stderr, "single cmd\n");
    fork_pid = fork();
    if (fork_pid == -1)
    {
        fprintf(stderr, "fork error\n");
        return;
    }
    if (fork_pid == 0)
    {
        prepare_cmd(d_exe, d_shell, cmd);
        handle_dup_fd_single_cmd(d_pip, d_exe);
        if (execve(d_exe->cmd_path, d_exe->cmd_n_arg, d_exe->env_cpy) == -1)
        {
            fprintf(stderr, "execve error\n");
            return;
        }
    }
    else
        waitpid(fork_pid, &status, 0);
}

void handle_dup_fd_single_cmd(t_pipe *d_pip, t_exec *exe)
{
    //fprintf(stderr, "handle_dup_fd_single\n");
	handle_redirections(exe, d_pip);
    if (d_pip->infile)
    {
        setup_infile_cmd(d_pip);
    }
    if (d_pip->outfile)
    {
        setup_outfile_cmd(d_pip, exe);
    }
}

void		child_process_0(t_pipe *d_pip, t_exec *d_exe, t_shell *d_shell, char *cmd)
{
	int		fork_pid;

	fork_pid = fork();
	if (fork_pid == -1)
		fprintf(stderr, "fork errot\n"); //perror_msg();
	if (fork_pid == 0)
	{
		//fprintf(stderr, ">>child proces_0: %s\n", cmd);
		close_pipes(d_pip, 1);
        prepare_cmd(d_exe, d_shell, cmd);
        fprintf(stderr, "cmd_path child 0 : %s\n", d_exe->cmd_path);
		handle_redirections(d_exe, d_pip);
		if (d_exe->cmd_number == 0)
			first_cmd(d_pip, d_exe);
		else if (d_exe->cmd_number == d_exe->number_of_pipes)
			last_cmd(d_pip, 0, d_exe);
		else
			middle_cmd(d_pip, d_exe, 0);
		if (execve (d_exe->cmd_path, d_exe->cmd_n_arg, d_exe->env_cpy) == -1)
			fprintf(stderr, "error excve\n");
	}
	close_pipes(d_pip, 3);
	pipe(d_pip->fd_pipe1);
}

void	child_process_1(t_pipe *d, t_exec *d_exe, t_shell *d_shell, char *cmd)
{
	int		fork_pid;
	//fprintf(stderr, ">>child proces_1: %s\n", cmd);
	fork_pid = fork();

	if (fork_pid == -1)
		fprintf(stderr, "fork errot\n"); //perror_msg();
	if (fork_pid == 0)
	{
		close_pipes(d, 2);
        prepare_cmd(d_exe, d_shell, cmd);
        fprintf(stderr, "cmd_path child 1 : %s\n", d_exe->cmd_path);
		handle_redirections(d_exe, d);
		if (d_exe->cmd_number == d_exe->number_of_pipes)
		{
			//fprintf(stderr, "last_cmd child_1\n");
			last_cmd(d, 1, d_exe);
		}
		else
		{
			//fprintf(stderr, "middle_cmd child_1\n");
			middle_cmd(d, d_exe, 1);
		}
		if (execve (d_exe->cmd_path, d_exe->cmd_n_arg, d_exe->env_cpy) == -1)
			fprintf(stderr, "error excve\n");//handle_exec_err(d->fd_pipe1[1], d_exe->cmd_n_arg, cmd_path);
	}
	close_pipes(d, 4);
	pipe(d->fd_pipe2);
}

void prepare_cmd(t_exec *d_exe, t_shell *d_shell, char *cmd)
{
	d_exe->path = get_path(d_exe->env_cpy);
	d_exe->access_path = ft_split_exec(d_exe->path, ':', 1);
	d_exe->cmd_n_arg = ft_split_exec(cmd, ' ', 0);
	d_exe->cmd_path = get_cmd_path(d_exe->cmd_n_arg[0], d_exe, &d_shell->trash_lst);
}