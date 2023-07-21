#include "minishell.h"
#include <errno.h>

void close_pipes(t_pipe *d, int process)
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

void create_heredoc_tab(t_exec *exe)
{
	char **heredoc_tab;

	heredoc_tab = ft_split_exec(exe->heredoc[exe->idx], ' ', 0);
	exe->heredoc = heredoc_tab;
}

void remove_prefixe_outfile(char **outfile_tab)
{
	int i;

	i = 0;
	while(outfile_tab[i])
	{
		outfile_tab[i] = outfile_tab[i] + 2;
		i++;
	}
	i = 0;
	while(outfile_tab[i])
	{
		fprintf(stderr, "check o_[%d]: %s\n", i, outfile_tab[i]);
		i++;
	}
}