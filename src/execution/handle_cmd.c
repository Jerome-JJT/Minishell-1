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
	//fprintf(stderr, "gwt cmd path\n");
	if (cmd)
	{
		if (info->access_path)
		{
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
		}
	}
	//fprintf(stderr, "ft_get_command path; %s\n", cmd);
	command_not_found(cmd);
	exit(1);
	return (NULL);
}

void	first_cmd(t_pipe *d, t_exec *d_exe)
{
	//fprintf(stderr, "first_cmd\n");
	// fprintf(stderr, "first_cmd infile:%s\n", d->infile);
	// fprintf(stderr, "first_cmd outfile:%s\n", d->outfile);
	if (d->infile)
	{
		setup_infile_cmd(d, d_exe);
	}
	if (d->outfile)
	{
		setup_outfile_cmd(d, d_exe);
	}
	else
	{
		if(dup2(d->fd_pipe2[1], STDOUT_FILENO) == -1)
			perror_msg_system(4, d_exe);
		close_pipes(d, 2);
	}
}

void	last_cmd(t_pipe *d, int process, t_exec *d_exe)
{
	//fprintf(stderr, "last_cmd\n");
	if (d->infile)
	{
		setup_infile_cmd(d, d_exe);
	}
	else
	{
		if (process == 0)
		{
			if (dup2 (d->fd_pipe1[0], STDIN_FILENO) == -1)
				perror_msg_system(4, d_exe);
			close_pipes(d, 2);
		}
		if (process == 1)
		{
			if (dup2 (d->fd_pipe2[0], STDIN_FILENO) == -1)
				perror_msg_system(4, d_exe);
			close_pipes(d, 1);
		}
	}
	if (d->outfile)
	{
		setup_outfile_cmd(d, d_exe);
	}
}

void	middle_cmd(t_pipe *d, t_exec *exe, int process)
{
	(void)exe;
	//fprintf(stderr, "middle_cmd\n");
	if (d->infile)
	{
		//fprintf(stderr, "infile in middle_cmd: %s\n", d->infile);
		setup_infile_cmd(d, exe);
	}
	else
	{
		if (process == 0)
			setup_middle_cmd(d, 0, exe);
		if (process == 1)
			setup_middle_cmd(d, 1, exe);
	}
	if (d->outfile)
		setup_outfile_cmd(d, exe);
	else
	{
		if (process == 0)
		{
			setup_middle_cmd(d, 2, exe);
		}
		if (process == 1)
		{
			setup_middle_cmd(d, 3, exe);
		}
	}
}

void setup_infile_cmd(t_pipe *d_pipe, t_exec *exe)
{
	//fprintf(stderr, ">>steup infile cmd\n");
	d_pipe->fd_in = open(d_pipe->infile, O_RDONLY);
	if (d_pipe->fd_in == -1)
    {
        write(2, "error opening infile\n", 21);
        return;
    }
	if (dup2(d_pipe->fd_in, STDIN_FILENO) == -1)
	{
		perror_msg_system(4, exe);
		return; // AJOUT
	}
	close(d_pipe->fd_in);
	if (d_pipe->fd_in == -1)
		perror_msg_system(2, exe);
}

void setup_outfile_cmd(t_pipe *d_pipe, t_exec *d_exe)
{
	(void)d_exe;
	//fprintf(stderr, "<< setup outfile  command idx : %d\n", d_exe->idx);
	if(d_exe->last_append)
	{
		//write(2, "setup_outfile_cmd idx : %d: last->append existant : %s\n", d_exe->idx, d_exe->last_append);
		d_pipe->fd_out = open (d_pipe->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else	// AJOUT PB CAT-E CAT -E CAT -E
	{
		//fprintf(stderr, "setup_outfile_cmd : open d_pipe->outfile\n");
		d_pipe->fd_out = open (d_pipe->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	if (d_pipe->fd_out == -1)
	{
		write(2, "error fd out\n", 13); //error_msg(d->outfile);
		return;
	}
	if(dup2 (d_pipe->fd_out, STDOUT_FILENO) == -1)
	{
		perror_msg_system(4, d_exe);
		return; // AJOUT
	}
	close(d_pipe->fd_out);
	if (d_pipe->fd_out == -1)
		perror_msg_system(2, d_exe);
}

void setup_middle_cmd(t_pipe *d_pipe, int option, t_exec *exe)
{
	if (option == 0)
	{
		if (dup2(d_pipe->fd_pipe1[0], STDIN_FILENO) == -1)
			perror_msg_system(4, exe);
	}
	if (option == 1)
	{
		if (dup2(d_pipe->fd_pipe2[0], STDIN_FILENO) == -1)
			perror_msg_system(4, exe);
	}
	if (option == 2)
	{
		if (dup2(d_pipe->fd_pipe2[1], STDOUT_FILENO) == -1)
			perror_msg_system(4, exe);
		close_pipes(d_pipe, 2);
	}
	if (option == 3)
	{
		if (dup2(d_pipe->fd_pipe1[1], STDOUT_FILENO) == -1)
			perror_msg_system(4, exe);
		close_pipes(d_pipe, 1);
	}
}
