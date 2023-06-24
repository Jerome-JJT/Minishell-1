#include "../../minishell.h"

/* ---------------- 1.strcpy with sep. char ---------------------*/
static void	cpy_var(char *dst, char *src, char sep)
{
	int	i;

	i = 0;
	while (src[i] != sep)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

/* ----------------------- 2. Split var. env. ---------------------------*/
char	**ft_split_var(char *var)
{
	char	**tab;
	int		i;

	tab = malloc(3 * sizeof(char *));
	if (!tab)
		return (NULL);
	tab[2] = NULL;
	i = 0;
	while (tab[i] != NULL)
	{
		tab[i] = malloc(200 * sizeof(char));
		if (!tab[i])
			printf("Erreur allocation ft_split_var\n");
		i++;
	}
	cpy_var(tab[0], var, '=');
	while (*var != '=')
		var++;
	var++;
	cpy_var(tab[1], var, '\0');
	return (tab);
}

/* ---------------------------- 3.Check valid quote --------------------------------*/
int	ft_checkquote(char *str)
{
	int	s_quote;
	int	d_quote;
	int	i;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			s_quote++;
		else if (str[i] == '\"')
			d_quote++;
		i++;
	}
	if (s_quote % 2 != 0 || d_quote % 2 != 0)
		return (1);
	return (0);
}
/* ---------------------------- 4.Check char is quote--------------------------------*/
int	ft_isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

/* -------------------- 5.Check char is sigle ----------------------------*/
int	ft_issigle(char c)
{
	if (ft_isprint(c) && !ft_isalnum(c))
			return (1);
	return (0);
}
