#include "minishell.h"
#include <errno.h>

void	command_not_found(char *cmd)
{
	char	*msg_err;
	char	*tmp;

	tmp = strjoin_exec("minishell: Command not found: ", cmd);
	msg_err = strjoin_exec(tmp, "\n");
	ft_putstr_fd(msg_err, 2);
	// free(tmp);
	// free(msg_err);
	//printf("Command '%s' not found\n", cmd);
	exit(127);
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

int perror_msg_system(int error_type)
{
	if (error_type == 1)
	{
		g_errno = errno;
		perror("Fork");
		return(g_errno);
	}
	if (error_type == 2)
	{
		g_errno = errno;
		perror("Pipe");
		return(g_errno);
	}
	if (error_type == 3)
	{
		g_errno = errno;
		perror("Execve");
		return(g_errno);
	}
		if (error_type == 4)
	{
		g_errno = errno;
		perror("Dup");
		return(g_errno);
	}
	return (0);
}