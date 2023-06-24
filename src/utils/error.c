#include "../../minishell.h"

// static void	ft_other_error(int errno, char *str)
// {

// }

int	ft_error_msg(int errno, char *str)
{
	if (errno == 1 && str == NULL)
	{
		printf("exit\n");
		printf(""RED"minishell"RESET": exit: too many arguments\n");
		g_errno = 1;
	}
	if (errno == 1)
	{
		printf(""RED"bash"RESET": %s: No such file or directory\n", str);
		g_errno = errno;
	}
	else if (errno == 126)
	{
		printf(""RED"env"RESET": %s: Premission denied\n", str);
		g_errno = errno;
	}
	else if (errno == 127 && str == NULL)
	{
		printf(""RED"env"RESET": %d: No such file or directory\n", g_errno);
		g_errno = errno;
	}
	else if (errno == 127 && str != NULL)
	{
		printf(""RED"env"RESET": %s: No such file or directory\n", str);
		g_errno = errno;
	}
	else if (errno == 258 && str == NULL)
	{
		printf(""RED"bash"RESET": syntax error near unexpected token `newline\'\n");
		g_errno = errno;
	}
	else if (errno == 258)
	{
		printf(""RED"bash"RESET": syntax error near unexpected token `%s\'\n", str);
		g_errno = errno;
	}
	// else
	// 	ft_other_error(errno, str);
	return (1);
}