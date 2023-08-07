#include "minishell.h"
#include <errno.h>

void	command_not_found(char *cmd)
{
	char	*msg_err;
	char	*tmp;
	g_errno = 127;
	if (cmd)
	{
		tmp = strjoin_exec("Minishell: Command not found: ", cmd);
		msg_err = strjoin_exec(tmp, "\n");
		ft_putstr_fd(msg_err, 2);
	}
	else
	{
		write(2, "Minishell: : Command not found\n", 31);
	}
	// free(tmp);
	// free(msg_err);
	//printf("Command '%s' not found\n", cmd);
	exit (EXIT_FAILURE);
}

void error_infile_outfile(int error_nb, t_exec *exe)
{
	(void)exe;
	if(errno == 9)
	{
		write(2, "No such file or directory\n", 26);
		exit(EXIT_FAILURE);
	}
	if (error_nb == 2)
	{
		write(2, "heredoc error\n", 14);
		exit(EXIT_FAILURE);
	}
}

int perror_msg_system(int errn)
{
	fprintf(stderr, ">>errno: %d\n", errno);
	fprintf(stderr, ">>errn: %d\n", errn);
	if (errn == 7)
	{
		perror("Fork");
	}
	else if (errn == 2)
	{
		perror("Pipe");
	}
	else if (errn == 3)
	{
		perror("Execve");
	}
	else if (errn == 4)
	{
		perror("Dup");
	}
	else if (errno == 1)
	{
		perror("Open");
	}
	else if (errno == 9)
	{
		perror("Close");
		///exit(EXIT_FAILURE);
	}
	else if (errno == 2 || errno == 0)
	{
		perror("Open");
		//exit(EXIT_FAILURE);
	}
	exit (EXIT_FAILURE);
	g_errno = errno;
	//return(g_errno);
	exit(EXIT_FAILURE);
	return(1);
}
