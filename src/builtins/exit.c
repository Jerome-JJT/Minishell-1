#include "../../minishell.h"

static int	ft_isonlyspace(char *str)
{
	int	len_max;

	len_max = ft_strlen(str);
	while (*str)
	{
		if (*str == ' ')
			len_max--;
		str++;
	}
	if (len_max > 0)
		return (0);
	return (1);
}
/* ------------------------- 1. Check if alpha is in str ------------------------------*/
static int	check_digitchar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '\0')
			ft_error_msg(255, str, "exit");
		i++;
	}
	return (0);
}

/* ------------------------- 2. Check if str is "--" ------------------------------*/
static int	check_line(char **arg)
{
	print_tab(arg, "check_line");
	if (!arg)
		exit (g_errno);
	else if (ft_isdigit(**arg) == 0)
		ft_error_msg(255, *arg, "exit");
	else
	{
		check_digitchar(*arg);
		if (*(arg + 1) != NULL)
			ft_error_msg(1, NULL, "exit");
		else
		{
			printf("exit\n");
			exit (ft_atoi(*arg));
		}
	}
	return (0);
}


/* ------------------------- 3. Main fonction exit ------------------------------*/
int	exit_minishell(char *arg, t_dlist **trash)
{
	char	**tab;
	char	*s_tmp;

	if (!arg)
		exit (g_errno);
	printf("Entrée exit: %s\n", arg);
	remove_quote(arg);
	if (ft_isonlyspace(arg))
		ft_error_msg(255, arg, "exit");
	s_tmp = ft_strtrim(arg, " ", trash);
	tab = ft_split(s_tmp, ' ', trash);
	print_tab(tab, "Tab with str");
	if (!tab)
	{
		printf("1\n");
		exit (g_errno);
	}
	else if (strncmp(*tab, "--", 3) == 0)
	{
		printf("3\n");
		check_line(tab + 1);
	}
	else
	{
		printf("4\n");
		// printf("tab + 1 = %s\n", *(tab + 1));
		check_digitchar(*tab);
		if (*(tab + 1) != NULL)
		{
			printf("5\n");
			return (ft_error_msg(1, NULL, "exit"));
		}
		printf("6\n");
		printf("exit\n");
		exit (ft_atoi(*tab));
	}
	// printf("7\n");
	return (0);
}
