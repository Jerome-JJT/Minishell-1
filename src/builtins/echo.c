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
static int	check_n(char *str)
{
	int	check;
	int	i;
	int	j;

	check = 0;
	i = 0;
	j = 0;
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		if (ft_strncmp(str, "-n", 3) == 0)
			return (1);
		else
		{
			while(str[i + 2] == 'n')
				i++;
			if (str[i + 2] != '\0' && ft_isalpha(str[i + 2]))
				return (0);
			else
				return (2);
		}
	}
	return (0);
}

/* -------------------- 3. Echo main function -----------------------*/
void	echo_minishell(char *str, t_dlist **trash)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!str || *str == '\0')
		printf("\n");
	else
	{
		if (*str == '\"')
			remove_quote(str);
		tmp = ft_split(str, ' ', trash);
		if (!tmp)
		{
			printf("\n");
			return ;
		}
		if (check_n(*tmp) == 2 && tmp + 1 != NULL)
			print_echo(tmp + 1, 1);
		else if (check_n(*tmp) == 1)
		{
			while (ft_strncmp(tmp[i], "-n", 3) == 0)
				i++;
			if (tmp + i != NULL)
				print_echo(tmp + i, 1);
		}
		else if (check_n(*tmp) == 0)
			print_echo(tmp, 0);
	}
}
