#include "minishell.h"
#include <errno.h>

void	close_pipes(t_pipe *d, int process)
{
	if (process == 1)
	{
		close(d->fd_pipe1[1]);
		close(d->fd_pipe2[0]);
	}
	if (process == 2)
	{
		close(d->fd_pipe1[0]);
		close(d->fd_pipe2[1]);
	}
	if (process == 3)
	{
		close(d->fd_pipe1[0]);
		close(d->fd_pipe1[1]);
	}
	if (process == 4)
	{
		close(d->fd_pipe2[1]);
		close(d->fd_pipe2[0]);
	}
}

void handle_redirections(t_exec *exe, t_pipe *pipe)
{
	//fprintf(stderr, "before redi_infile:%s\n", exe->redi_infile[0]);
	if (exe->redi_infile[0])
		exe->redi_infile = handle_infile(exe);
	//fprintf(stderr, "after redi_infile:%s\n", exe->redi_infile[0]);
	//fprintf(stderr, "before redi_outfile:%s\n", exe->redi_outfile[0]);
	if (exe->redi_outfile[0])
		exe->redi_outfile = handle_outfile(exe);
	//fprintf(stderr, "after redi_outfile:%s\n", exe->redi_outfile[0]);
	init_struc_pipe(pipe, exe->redi_infile[0], exe->redi_outfile[0], exe);
//	control_files(pipe->infile, pipe->outfile);
}

char	**handle_infile(t_exec *exe)
{
	int i;
	int in;

	i = 0;
	while(exe->redi_infile[i])
	{
		in = open(exe->redi_infile[i], O_RDONLY, 0644);
		close(in);
		if (in == -1)
			error_infile_outfile(0, exe);
		i++;
	}
	i--;
	return(&exe->redi_infile[i]);
}

char	**handle_outfile(t_exec *exe)
{
	int i;
	int out;

	i = 0;
	while(exe->redi_outfile[i])
	{
		out = open(exe->redi_outfile[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(out);
		i++;
	}
	i--;
	return(&exe->redi_outfile[i]);
}
