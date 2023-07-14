#include "../../minishell.h"

/* ------------------------- fonction exit ------------------------------*/
void	exit_minishell(char **arg)
{
	if (!*arg)
	{
		printf("exit\n");
		exit (g_errno);
	}
	else if (ft_isalpha(**arg))
	{
		printf("minishell: exit: %s: numeric argument required", *arg);
		exit (255);
	}
	else if (ft_tabsize(arg) > 1)
		ft_error_msg(1, NULL);
	else
	{
		printf("exit\n");
		exit(ft_atoi(*arg));
	}
}

/*
Test déjà effectué:
--------------------------------------------|
1.exit = quitte le programme avec le dernier errno
2.exit 123 = quitte le programme avec erreur 123
3.exit abc = erreur 255
4.exit 123 123 = erreur 1 - trop d'arguments
5. exit 123a = erreur 255 ->> à corriger /!\






*/
