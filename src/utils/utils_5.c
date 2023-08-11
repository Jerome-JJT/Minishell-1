#include "../../minishell.h"

/* -------------------- 1.If Here_Doc ----------------------------*/
int	is_here_doc(t_tok *token)
{
	t_tok	*ptr;

	if (!token)
		return (0);
	ptr = token;
	while (ptr != NULL && ptr->next != NULL)
		ptr = ptr->next;
	if (ptr->type == H_D)
		return (1);
	else if (!ptr->prev)
		return (0);
	else if (ptr->type == SPACEE && ptr->prev->type == H_D)
		return (1);
	return (0);
}

/* -------------------- 2.If buff has $env_var ----------------------------*/
char	*if_env_var_word(char *str,  t_env *env, t_dlist **trash)
{
	int		i;
	int 	j;
	char	*tmp[3];
	t_list	*ret;

	i = 0;
	j = 0;
	tmp[0] = NULL;
	ret = NULL;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (!ft_isparsing_char(str[i]) && ft_issigle(str[i])
			&& str[i])
	{
		while (ft_isprint(str[i + j])
				&& !ft_isparsing_char(str[i + j]))
			j++;
		tmp[1] = ft_substr(str + i, 0, j, trash);
	}
	tmp[2] = ft_substr(str, 0, i, trash);
	ret = find_var_env(env, tmp[2], 1);
	if (ret != NULL)
		tmp[0] = ft_strdup_pars(ret->valeur, trash);
	if (j > 0)
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	return (tmp[0]);
}

/* -------------------- 3.If buff has $? ----------------------------*/
char	*if_errno_word(char *str, t_dlist **trash)
{
	int		i;
	char	*tmp[2];

	i = 0;
	if (!ft_isparsing_char(*str))
	{
		while (str[i] != '\0' && !ft_isparsing_char(str[i]))
			i++;
		tmp[1] = ft_substr(str, 0, i, trash);
	}
	tmp[0] = ft_strdup(ft_itoa(g_errno, trash), trash);
	if (i > 0)
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	return (tmp[0]);
}

/* -------------------- 4.Strdup for special case ----------------------------*/
char	*ft_strdup_pars(const char *str, t_dlist **trash)
{
	int		i;
	int		len;
	char	*s_cpy;

	if (!str || !*str)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	s_cpy = my_malloc(len + 1, sizeof(char), trash);
	if (!s_cpy)
		return (0);
	while (i <= len && str[i])
	{
		s_cpy[i] = str[i];
		i++;
	}
	s_cpy[i] = 0;
	return (s_cpy);
}

// /* -------------------- 5. Remplace oldchar -> newchar ----------------------------*/
// void	remplace_char(char *s, char old, char new)
// {
// 	if (!s || !*s)
// 		return ;
// 	while (*s)
// 	{
// 		if (*s == old)
// 			*s = new;
// 		s++;
// 	}
// }