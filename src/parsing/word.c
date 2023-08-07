#include "../../minishell.h"

/* -------------------- 1.If Here_Doc ----------------------------*/
static int	is_here_doc(t_tok *token)
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

/* -------------------- 2.If $env_var ----------------------------*/
static char	*if_env_var(char *str,  t_env *env, t_dlist **trash)
{
	int		i;
	int 	j;
	char	*tmp[3];
	t_list	*ret;

	i = 0;
	j = 0;
	tmp[0] = "";
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
	if (ret)
		tmp[0] = ft_strdup(ret->valeur, trash);
	if (j > 0)
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	return (tmp[0]);
}

/* -------------------- 3.If $? ----------------------------*/
static char	*if_errno(char *str, t_dlist **trash)
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

/* -------------------- 4.Check if $ exist ----------------------------*/
static char	*ft_word_d(char *str, t_env *env, t_dlist **trash)
{
	int		i;
	char	*tmp[2];

	i = 0;
	tmp[0] = str;
	while (!ft_isparsing_char(str[i]) && str[i] != '$')
		i++;
	if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
		tmp[0] = ft_substr(str, 0, i, trash);
	if (ft_isalnum(str[i + 1]))
	{
		tmp[1] = if_env_var(str + (i + 1), env, trash);
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	}
	else if (str[i + 1] == '?')
	{
		tmp[1] = if_errno(str + (i + 2), trash);
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	}
	return (tmp[0]);
}

/* -------------------- 5.Word function ----------------------------*/
char	*ft_word(char *str, t_shell *info)
{
	int		i;
	int		check;
	char	*tmp;

	i = 0;
	check = 0;
	tmp = NULL;
	//fprintf(stderr, "tok:%s\n", info->token->tok);
	if (info->token && is_here_doc(info->token))
	{
		while (!ft_isparsing_char(str[i]))
			i++;
		creat_and_add(tmp, str, WORD, i, info);
	}
	else
	{
		while (!ft_isparsing_char(str[i]))
		{
			if (str[i] == '$' && check == 0)
		{
			tmp = ft_word_d(str, info->env, &info->trash_lst);
			check++;
		}
			else if (str[i] == '$' && check != 0)
				tmp = ft_word_d(tmp, info->env, &info->trash_lst);

			i++;
		}
		creat_and_add(tmp, str, WORD, i, info);
	}
	return (str + i);
}
