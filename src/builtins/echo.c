#include "../../minishell.h"

/* -------------------- 1. Char is separation -----------------------*/
int	ft_issep(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

/* -------------------- 2.Echo with -n option or not -----------------------*/
static void	echo_n(char **tab, int option_n)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (ft_issep(tab[i][0]) && ft_strlen(tab[i]) < 2)
			break ;
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(" ");
		i++;
	}
	if (option_n == 0)
		printf("\n");
}

/* -------------------- 3. Echo main function -----------------------*/
void	echo_minishell(char **tab)
{
	if (!*tab)
		printf("\n");
	else
	{
		if (ft_strncmp(*tab, "-n", 3) == 0)
			echo_n(tab + 1, 1);
		else
			echo_n(tab, 0);
	}
}
