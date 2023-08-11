#include "../../minishell.h"

// static void	ft_other_error(int errno, char *str)
// {

// }

int	ft_error_msg(int errn, char *str, char *ft)
{
	(void) ft;
	g_errno = errn;
	if (errn == 1 && !str)
	{
		printf("exit\n");
		printf(""RED"minishell"RESET": exit: too many arguments\n");
	}
	else if (errn == 1)
	{
		printf(""RED"minishell"RESET": cd: %s: Not a directory\n", str);
		g_errno = errn;
	}
	else if (errn == 126)
	{
		printf(""RED"env"RESET": %s: Premission denied\n", str);
		g_errno = errn;
	}
	else if (errn == 127 && !str)
	{
		printf(""RED"env"RESET": %d: No such file or directory\n", g_errno);
		g_errno = errn;
	}
	else if (errn == 127)
	{
		printf(""RED"env"RESET": %s: No such file or directory\n", str);
		g_errno = errn;
	}
	else if(errn == 255)
	{
		printf("exit\n");
		printf(""RED"minishell"RESET": exit: %s: numeric argument required\n", str);
		exit (g_errno);
	}
	else if (errn == 258 && str == NULL)
	{
		printf(""RED"minishell"RESET": syntax error near unexpected token `newline\'\n");
		g_errno = errn;
	}
	else if (errn == 258)
	{
		printf(""RED"minishell"RESET": syntax error near unexpected token `%s\'\n", str);
		g_errno = errn;
	}
	// else
	// 	ft_other_error(errno, str);
	return (1);
}