#include "../../minishell.h"

/* -------------------- 1.Echo with -n option or not -----------------------*/
static void	echo_n(char **tab, int option_n)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(" ");
		i++;
	}
	if (option_n == 0)
		printf("\n");
}

/* -------------------- 2. Echo main function -----------------------*/
void	echo_minishell(char **tab)
{
	if (!*tab)
		printf("\n");
	else
	{
		*tab = remove_quote(*tab);
		if (ft_strncmp(*tab, "-n", 3) == 0)
			echo_n(tab + 1, 1);
		else
			echo_n(tab, 0);
	}
}
