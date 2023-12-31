#include "minishell.h"


void	init_struc_pipe(t_pipe *d, char *infile, char *outfile, t_exec *exe)
{
	(void)exe;
	d->infile = infile;
	d->outfile = outfile;
}

void	handle_pipes(int (*fd1)[2], int (*fd2)[2], t_exec *exe)
{
	if (pipe(*fd1) == -1 || pipe(*fd2) == -1)
		perror_msg_system(2, exe);//fprintf(stderr, "error handles_pipes\n");
}
