#include "../../minishell.h"

/* ---------------- 1.strcpy with sep. char ---------------------*/
void cpy_var(char *dst, char *src, char sep)
{
    int i = 0;

    while (src[i] != sep && src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }

    dst[i] = '\0';
}

char **ft_split_var(char *var, t_dlist **trash)
{
    char    **tab;
    char    *tmp;

    tab = my_malloc(3, sizeof(char *), trash);
    if (!tab)
    {
        printf("Error allocating memory for tab\n");
        return NULL;
    }
    tab[2] = NULL;
    tab[0] = my_malloc((ft_strlen(var) + 1), sizeof(char), trash);
    tab[1] = my_malloc((ft_strlen(var) + 1), sizeof(char), trash);
    cpy_var(tab[0], var, '=');
    tmp = ft_strchr(var, '=');
    if (tmp)
    {
        tmp++; // Move past the '=' character
        cpy_var(tab[1], tmp, '\0');
    }
    return tab;
}

/* ---------------------------- 3.Check valid quote --------------------------------*/
int	ft_checkquote(char *str, int s_or_d)
{
    int i;

    i = 1;
	if (s_or_d == 1)
    {
        while (str[i] != '\'' && str[i])
            i++;
        if (str[i] == '\0')
            return (1);
    }
    if (s_or_d == 2)
    {
        while (str[i] != '\"' && str[i])
            i++;
        if (str[i] == '\0')
            return (1);
    }
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
