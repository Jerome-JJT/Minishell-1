#include "../../minishell.h"

/* -------------------- test -----------------------*/
int	ft_issep(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

/* -------------------- test -----------------------*/
static void	echo_n(char **tab, int option_n)
{
	int		i;

	i = option_n;
	while (tab[i])
	{
		if (ft_issep(tab[i][0]) && ft_strlen(tab[i]) < 2)
			break ;
		printf("%s", tab[i]);
		i++;
	}
	if (option_n == 0)
		printf("\n");
}

/* -------------------- 4. Echo -----------------------*/
void	echo_minishell(char **tab)
{
	if (!*tab || ft_issep(**tab))
		printf("\n");
	else
	{
		if (ft_strncmp(*tab, "-n", 3) == 0)
			echo_n(tab + 2, 1);
		else
			echo_n(tab, 0);
	}
}

/*
Test déjà effectué:
--------------------------------------------|
1.echo = '\n'
2.echo salut = salut
3.echo $? = 0 -> if erreur avant = errno
4.echo $NOM_VARIABLE = valeur variable ($USER = nrossel)
5.echo $?$?$?$? = 0000
6.echo $?1 = 01
8.echo $USER$? = nrossel0
9.echo $USER$abc = nrossel ->> à corriger /!\
10. echo $salut = '\n' ->> à corriger /!\







*/