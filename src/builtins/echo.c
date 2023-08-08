#include "../../minishell.h"

/* -------------------- 1.Echo with -n option or not -----------------------*/
static void	echo_n(char **tab, int option_n)
{
	int		i;

	i = 0;
	if (!*tab)
		return ;
	else
	{
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
}

/* -------------------- 2. Echo main function -----------------------*/
void	echo_minishell(char *str, t_dlist **trash)
{
	int		check;
	int		i;
	char	**tmp;

	check = 0;
	i = 0;
	if (!str || !*str)
		printf("\n");
	else
	{
		if (*str == '\"')
			remove_quote(str);
		tmp = ft_split(str, ' ', trash);
		if (tmp[1] != NULL)
		{
			while (ft_strncmp(tmp[i++], "-n", 3) == 0)
				check = 1;
			if (check == 1)
				echo_n(tmp + i, 1);
			else
				echo_n(tmp, 0);
		}
	}
}
