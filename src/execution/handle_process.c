#include "minishell.h"
#include <errno.h>

void create_infile_tab(t_exec *exe);
void create_outfile_tab(t_exec *exe);

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

void create_infile_tab(t_exec *exe)
{
	char **infile_tab;
	//int i = 0;

	infile_tab = ft_split_exec(exe->redi_infile[exe->idx], ' ', 0);
	// while (infile_tab[i])
	// {
	// 	fprintf(stderr, "tab[%d] = %s\n", i, infile_tab[i]);
	// 	i++;
	// }
	exe->redi_infile = infile_tab;
}

void create_outfile_tab(t_exec *exe)
{
	char **outfile_tab;
	//int i = 0;

	outfile_tab = ft_split_exec(exe->redi_outfile[exe->idx], ' ', 0);
	// while (outfile_tab[i])
	// {
	// 	fprintf(stderr, "tab[%d] = %s\n", i, infile_tab[i]);
	// 	i++;
	// }
	exe->redi_outfile = outfile_tab;
}

void handle_redirections(t_exec *exe, t_pipe *pipe)
{
	// fprintf(stderr, ">>>HANDLE FILES\n");
	//fprintf(stderr, "control idx: %d\n", exe->idx);
	// fprintf(stderr, "BEFORE control redi outfile[0]: %s\n", exe->heredoc[exe->idx]);
	//fprintf(stderr, "BEFORE control redi infile_idx: %s\n", exe->redi_infile[exe->idx]);
	//fprintf(stderr, "BEFORE control redi outfile_idx: %s\n", exe->redi_outfile[exe->idx]);
	if (exe->heredoc[exe->idx]) //((ft_strncmp((const char*)exe->str_heredoc, "", 1) != 0))	// AJOUT HEREDOC
	{
		//fprintf(stderr, "heredoc no empty\n");
		pipe->fd_in = open(".heredoc.txt", O_RDONLY); // A TESTER
		exe->redi_infile[exe->idx] = ".heredoc.txt";
	}
	else
	{
		//fprintf(stderr, "heredoc empty\n");
		// fprintf(stderr, "check value redi_in: %s\n", exe->redi_infile[0]);
		if (exe->redi_infile[exe->idx] != NULL)
		{
			//create_infile_tab(exe);
			// fprintf(stderr, "TAB control redi infile_idx: %d\n", exe->idx);
			// fprintf(stderr, "TAB control redi infile_idx[1]: %s\n", exe->redi_infile[0]);
			exe->redi_infile = handle_infile(exe);
		}
		else
			exe->redi_infile[0] = NULL;
	}
	if (exe->redi_outfile[exe->idx])
	{
		//create_outfile_tab(exe);
		// fprintf(stderr, "TAB control redi outfile_idx[0]: %s\n", exe->redi_outfile[0]);
		// fprintf(stderr, "TAB control redi outfile_idx[1]: %s\n", exe->redi_outfile[1]);
		exe->redi_outfile = handle_outfile(exe);
	}
	else
		exe->redi_outfile[0] = NULL;
	//fprintf(stderr, "AFTER control redi infile: %s\n", exe->redi_infile[0]);
	//fprintf(stderr, "AFTER control redi outfile: %s\n", exe->redi_outfile[0]);
	init_struc_pipe(pipe, exe->redi_infile[0], exe->redi_outfile[0], exe);
}

char **handle_infile(t_exec *exe)
{
	int i;
	int in;
	char **infile_tab;
	//fprintf(stderr, "handle infilee : %s\n", exe->redi_infile[0]);
	infile_tab = ft_split_exec(exe->redi_infile[exe->idx], ' ', 0);
	i = 0;
	if (infile_tab[0])
	{
		while (infile_tab[i])
		{
			in = open(infile_tab[i], O_RDONLY, 0644);
			close(in);
			if (in == -1)
				error_infile_outfile(0, exe);
			i++;
		}
		i--;
	}
	exe->redi_infile[0] = infile_tab[i];
	return (&exe->redi_infile[0]);
}

char **handle_outfile(t_exec *exe)
{
	int i;
	int out;
	char **outfile_tab;
	// fprintf(stderr, "handle outfilee 0 : %s\n", exe->redi_infile[exe->idx]);
	outfile_tab = ft_split_exec(exe->redi_outfile[exe->idx], ' ', 0);
	i = 0;
	if (outfile_tab[0])
	{
		while (outfile_tab[i])
		{
			out = open(outfile_tab[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(out);
			i++;
		}
		i--;
	}
	exe->redi_outfile[0] = outfile_tab[i];
	return (&exe->redi_outfile[0]);
}