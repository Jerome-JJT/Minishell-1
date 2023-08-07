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
void	echo_minishell(char **tab, t_dlist **trash)
{
	int	check;
	int	i;

	check = 0;
	i = -1;
	if (!*tab || !**tab)
		printf("\n");
	else
	{
		remove_quote(*tab);
		tab = ft_split(*tab, ' ', trash);
		while (ft_strncmp(tab[++i], "-n", 3) == 0)
			check = 1;
		if (check == 1)
			echo_n(tab + i, 1);
		else
			echo_n(tab, 0);
	}
}
