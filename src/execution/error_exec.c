#include "minishell.h"
#include <errno.h>

//static int is_a_path(char *cmd);

void	command_not_found(char *cmd)
{
	char	*msg_err;
	char	*tmp;
	g_errno = 127;

	// if (cmd && is_a_path(cmd) > 1)
	// {
	// 	tmp = strjoin_exec("Minishell(EXEC): ", cmd);
	// 	msg_err = strjoin_exec(tmp, ": Not a directory\n");
	// 	ft_putstr_fd(msg_err, 2);
	// }
	if (cmd && cmd[0] == '/')
	{
		tmp = strjoin_exec("Minishell(EXEC): ", cmd);
		msg_err = strjoin_exec(tmp, ": No such file or directory\n");
		ft_putstr_fd(msg_err, 2);
	}
	else if (cmd)
	{
		tmp = strjoin_exec("Minishell(EXEC): ", cmd);
		msg_err = strjoin_exec(tmp, ": command not found\n");
		ft_putstr_fd(msg_err, 2);
	}
	else
	{
		write(2, "Minishell(EXEC ELSE): : command not found\n", 42);
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
	//(stderr, ">>errno: %d\n", errno);
	fprintf(stderr, ">>errn: %d\n", errn);
	if (errn == 1 && (errno == EAGAIN || errno == ENOMEM))
	{
		perror("Fork");
	}
	else if (errn == 2 && (errno == EMFILE || errno == ENFILE || errno == EFAULT))
	{
		perror("Pipe");
	}
	else if (errn == 3 && (errno == EFAULT))
	{
		perror("Execve");
	}
	else if (errn == 4 && (errno == EBADF || errno == EBUSY))
	{
		perror("Dup2");
	}
	else if (errn == 5 && errno == EBADF)
	{
		perror("Dup");
	}
	else if (errn == 6 && (errno == EACCES || errno == ENOENT || errno == EEXIST || errno == EISDIR || errno == ENFILE))
	{
		perror("Close");
		///exit(EXIT_FAILURE);
	}
	else if (errn == 7 && (errno == EACCES || errno == ENOENT || errno == EEXIST || errno == EISDIR || errno == ENFILE))
	{
		perror("Open");
	}
	else if (errno == 0)
	{
		perror("");
		//exit(EXIT_FAILURE);
	}
	exit (EXIT_FAILURE);
	g_errno = errno;
	//return(g_errno);
	exit(EXIT_FAILURE);
	return(1);
}

// static int is_a_path(char *cmd)
// {
// 	int i;
// 	int count;

// 	i = 0;
// 	count = 0;

// 	while(cmd[i])
// 	{
// 		if (cmd[i] == '/')
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }
