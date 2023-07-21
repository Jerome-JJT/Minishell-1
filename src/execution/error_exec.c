#include "minishell.h"
#include <errno.h>

void	command_not_found(char *cmd)
{
	// char	*msg_err;
	// char	*tmp;

	// tmp = ft_strjoin("minishell: command not found: ", cmd, trash);
	// // msg_err = ft_strjoin(tmp, "\n");
	// ft_putstr_fd(msg_err, 2);
	// free(tmp);
	// free(msg_err);
	printf("Command '%s' not found\n", cmd);
	//exit(127);
}

void error_infile_outfile(int error_nb, t_exec *exe)
{
	(void)exe;
	fprintf(stderr, "error_in_out\n");
	if(errno == 9)
	{
		fprintf(stderr, "No such file or directory %d\n", errno);
		exit(EXIT_FAILURE);
	}
	if (error_nb == 2)
	{
		fprintf(stderr, "heredoc error\n");
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
	return (0);
}