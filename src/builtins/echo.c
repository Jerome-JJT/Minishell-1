#include "../../minishell.h"

/* -------------------- 1.Echo with -n option or not -----------------------*/
static void	print_echo(char **tab, int option_n)
{
	int		i;

	i = 0;
	if (!*tab)
		return ;
	if (!**tab)
		printf(" ");
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

/* -------------------- 2. Check -n variant -----------------------*/
static int	check_n(char **tab)
{
	int	check;
	int	i;
	int	j;

	check = 0;
	i = 0;
	while (ft_strncmp(tab[i], "-n", 2) == 0)
	{
		if (ft_strncmp(tab[i], "-n", 3))
		{
			j = 2;
			while(tab[i][j] == 'n')
				j++;
			if (tab[i][j] != '\0' && ft_isprint(tab[i][j]))
				return (i);
		}
		i++;
	}
	return (i);
}

/* -------------------- 3. Echo main function -----------------------*/
void	echo_minishell(char *str, t_dlist **trash)
{
	int		check;
	char	**tmp;

	check = 0;
	if (!str || *str == '\0')
		printf("\n");
	else
	{
		// fprintf(stderr, "%s\n", str);
		if (*str == '\"')
			remove_quote(str);
		tmp = ft_split(str, ' ', trash);
		if (!tmp)
		{
			printf("\n");
			return ;
		}
		check = check_n(tmp);
		if (check > 0)
			print_echo(tmp + check, 1);
		else
			print_echo(tmp, 0);
		// if (check_n(*tmp) == 2 && tmp + 1 != NULL)
		// 	print_echo(tmp + 1, 1);
		// else if (check_n(*tmp) == 1)
		// {
		// 	while (ft_strncmp(tmp[i], "-n", 3) == 0)
		// 		i++;
		// 	if (tmp + i != NULL)
		// 		print_echo(tmp + i, 1);
		// }
		// else if (check_n(*tmp) == 0)
		// 	print_echo(tmp, 0);
	}
}
