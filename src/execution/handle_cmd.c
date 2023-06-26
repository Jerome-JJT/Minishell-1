#include "minishell.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, t_exec *info, t_dlist **trash)
{
	int		i;
	char	*cmd_path;
	(void)trash;
	i = 0;
	while (info->access_path[i])
	{
		cmd_path = strjoin_exec(info->access_path[i], cmd);
		if (access (cmd_path, F_OK) == 0)
		{
			return (cmd_path);
		}
		else
		i++;
	}
	//fprintf(stderr, "ft_get_command path; %s\n", cmd);
	command_not_found(cmd);
	exit(1);
	return (NULL);
}

void	first_cmd(t_pipe *d, char *cmd_path, t_exec *d_exe)
{
	//fprintf(stderr, "first_cmd\n");
	(void)cmd_path;
	(void)d_exe;
	// fprintf(stderr, "first_cmd infile:%s\n", d->infile);
	// fprintf(stderr, "first_cmd outfile:%s\n", d->outfile);
	if (d->infile)
	{
		//fprintf(stderr, "infile in first_cmd: %s\n", d->infile);
		d->fd_in = open(d->infile, O_RDONLY);
		if (d->fd_in == -1)
        {
            fprintf(stderr, "error opening infile\n");
            return;
        }
		if (dup2(d->fd_in, STDIN_FILENO) == -1)
		{
			fprintf(stderr, "dup in error_first_cmd\n"); //handle_dup_err(d->fd_in, d->fd_pipe2[1], d_exe->cmd_n_arg, 0);
			return; // AJOUT
		}
		close(d->fd_in);
	}
	if (d->outfile)
	{
		//fprintf(stderr, "<<outfile in first command\n");
		d->fd_out = open (d->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (d->fd_out == -1)
		{
			//close(d->fd_out);
			fprintf(stderr, "error fd out\n"); //error_msg(d->outfile);
		}
		if(dup2 (d->fd_out, STDOUT_FILENO) == -1)
		{
			fprintf(stderr, "dup error_last_cmd_0\n"); //handle_dup_err(d->fd_out, d->fd_pipe1[0], d_exe->cmd_n_arg, 0);
			return; // AJOUT
		}
		close(d->fd_out); //
	}
	else
	{
		if(dup2(d->fd_pipe2[1], STDOUT_FILENO) == -1)
			fprintf(stderr, "dup out error_first_cmd\n");
		close_pipes(d, 2);
	}
}

void	last_cmd(t_pipe *d, char *cmd_path, int process, t_exec *d_exe)
{
	//fprintf(stderr, "last_cmd\n");
	(void)cmd_path;
	(void)d_exe;
	
	if (d->infile)
	{
		//fprintf(stderr, "infile in last_cmd: %s\n", d->infile);
		d->fd_in = open(d->infile, O_RDONLY);
		if (d->fd_in == -1)
        {
            fprintf(stderr, "error opening infile last_cmd\n");
            return;
        }
		if (dup2(d->fd_in, STDIN_FILENO) == -1)
			fprintf(stderr, "dup in error first_cmd\n"); //handle_dup_err(d->fd_in, d->fd_pipe2[1], d_exe->cmd_n_arg, 0);
		close(d->fd_in);
	}
	else
	{
		if (process == 0)
		{
			if (dup2 (d->fd_pipe1[0], STDIN_FILENO) == -1)
				fprintf(stderr, "dup error_last_cmd_0\n"); //handle_dup_err(d->fd_out, d->fd_pipe1[0], d_exe->cmd_n_arg, 0);
			close_pipes(d, 2);
		}
		if (process == 1)
		{
			if (dup2 (d->fd_pipe2[0], STDIN_FILENO) == -1)
				fprintf(stderr, "dup error_last_cmd_0\n");
			close_pipes(d, 1);
		}
	}

	if (d->outfile)
	{
		d->fd_out = open (d->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (d->fd_out == -1)
		{
			close(d->fd_out);
			fprintf(stderr, "error fd out\n"); //error_msg(d->outfile);
		}
		if(dup2 (d->fd_out, STDOUT_FILENO) == -1)
			fprintf(stderr, "dup error_last_cmd_0\n");
		close(d->fd_out); //
	}
}

void	middle_cmd(t_pipe *d, char *cmd_path, int process)
{
	//fprintf(stderr, "middle_cmd\n");
	(void)cmd_path;
	
	if (d->infile)
	{
		//fprintf(stderr, "infile in middle_cmd: %s\n", d->infile);
		d->fd_in = open(d->infile, O_RDONLY);
		if (dup2(d->fd_in, STDIN_FILENO) == -1)
			fprintf(stderr, "dup in error_first_cmd\n"); //handle_dup_err(d->fd_in, d->fd_pipe2[1], d_exe->cmd_n_arg, 0);
		close(d->fd_in);
	}
	else
	{
		if (process == 0)
		{
			if (dup2(d->fd_pipe1[0], STDIN_FILENO) == -1)
				fprintf(stderr, "dup error_middle_0\n");//handle_dup_err(0, d->fd_pipe1[0], d->cmd_n_arg, 1);
		}
		if (process == 1)
		{
			if (dup2 (d->fd_pipe2[0], STDIN_FILENO) == -1) 	// A CONTROLER PIPE
				fprintf(stderr, "dup error_last_cmd_0\n");
		}
	}
	if (d->outfile)
	{
		d->fd_out = open (d->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (d->fd_out == -1)
		{
			close(d->fd_out);
			fprintf(stderr, "error fd out\n"); //error_msg(d->outfile);
		}
		if(dup2 (d->fd_out, STDOUT_FILENO) == -1)
			fprintf(stderr, "dup error_last_cmd_0\n");
		close(d->fd_out); //
	}
	else
	{
		if (process == 0)
		{
			if (dup2(d->fd_pipe2[1], STDOUT_FILENO) == -1)
				fprintf(stderr, "dup error\n");//handle_dup_err(1, d->fd_pipe2[1], d->cmd_n_arg, 1);
			close_pipes(d, 2);
		}
		if (process == 1)
		{
			if (dup2(d->fd_pipe1[1], STDOUT_FILENO) == -1)
				fprintf(stderr, "dup error_middle_1\n");//handle_dup_err(1, d->fd_pipe1[1], d->cmd_n_arg, 1);
			close_pipes(d, 1);
		}
	}
}