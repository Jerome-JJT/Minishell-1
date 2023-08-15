#include "../../minishell.h"

// static void	ft_other_error(int errno, char *str)
// {

// }

int	ft_error_msg(int errn, char *str, char *ft, int num)
{
	(void) num;

	g_errno = errn;
	/* -------------------------------- Unset -------------------------------------- */ // -> √
	if (ft_strncmp(ft, "unset", 6) == 0)
	{
		if (errn == 1)
			printf(""RED"minishell"RESET": unset: `%s': not a valid identifier\n", str);
	}
	/* -------------------------------- Exit -------------------------------------- */ // -> √
	else if (ft_strncmp(ft, "exit", 5) == 0)
	{
		if (errn == 1)
		{
			printf("exit\n");
			printf(""RED"minishell"RESET": exit: too many arguments\n");
		}
		else if(errn == 255)
		{
			printf("exit\n");
			printf(""RED"minishell"RESET": exit: %s: numeric argument required\n", str);
			exit (g_errno);
		}
	}
	/* -------------------------------- Cd -------------------------------------- */
	else if (ft_strncmp(ft, "cd", 3) == 0)
	{
		if (errn == 1 && num == 1)
			printf(""RED"minishell"RESET": cd: %s: Not a directory\n", str);
		else if (errn == 1)
			printf(""RED"minishell"RESET": cd: %s: No such file or directory\n", str);
	}
	/* -------------------------------- Env -------------------------------------- */ // -> √
	else if (ft_strncmp(ft, "env", 4) == 0)
	{
		if (errn == 126)
			printf(""RED"env"RESET": %s: Premission denied\n", str);
		else if (errn == 127)
			printf(""RED"env"RESET": %s: No such file or directory\n", str);
	}
	/* -------------------------------- Syntax -------------------------------------- */
	else if (ft_strncmp(ft, "syntax", 7) == 0)
	{
		if (errn == 1 && num == 0)
			printf(""RED"env"RESET": %s: No such file or directory\n", str);
		else if (errn == 1 && num == 1)
			printf(""RED"minishell"RESET": stdin: Is a directory\n");
		else if (errn == 1 && num == 2)
			printf("Erreur lors de l'ouverture du fichier\n");
		else if (errn == 258 && !str)
			printf(""RED"minishell"RESET": syntax error near unexpected token `newline\'\n");
		else if (errn == 258)
			printf(""RED"minishell"RESET": syntax error near unexpected token `%s\'\n", str);
	}
	return (1);
}