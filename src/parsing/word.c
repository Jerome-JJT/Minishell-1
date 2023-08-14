#include "../../minishell.h"

/* -------------------- 1.Check if $ exist ----------------------------*/
static char	*ft_word_d(char *buffer, t_env *env, t_dlist **trash)
{
	int		i;
	char	*tmp[2];

	i = 0;
	tmp[0] = NULL;
	while (!ft_isparsing_char(buffer[i]) && buffer[i] != '$')
	{
		// printf("A.buffer[%d] = %c\n", i, buffer[i]);
		i++;
	}
	// printf("B.buffer[%d] = %c & ft_isalnum = %d\n", i, buffer[i], ft_isalnum(buffer[i + 1]));
	if (buffer[i] == '$' && (ft_isalnum(buffer[i + 1])|| buffer[i + 1] == '?'))
	{
		tmp[0] = ft_substr(buffer, 0, i, trash);
		// printf("tmp[0] = %s\n", tmp[0]);
	}
	i++;
	if (ft_isalnum(buffer[i]) || buffer[i] == '_')
	{
		tmp[1] = if_env_var_word(buffer + i, env, trash);
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	}
	else if (buffer[i] == '?')
	{
		tmp[1] = if_errno_word(buffer + (i + 1), trash);
		tmp[0] = ft_strjoin(tmp[0], tmp[1], trash);
	}
	return (tmp[0]);
}

/* -------------------- 2.Analys buffer ----------------------------*/
static char	*analys_buffer(char *ret, char *buffer, t_shell *info, int *index, int *if_$)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (!ft_isparsing_char(buffer[i]))
		{
			if (buffer[i] == '$' && !ft_isparsing_char(buffer[i + 1] && check == 0))
			{
				ret = ft_word_d(buffer, info->env, &info->trash_lst);
				check++;
			}
			else if (buffer[i] == '$' && check != 0)
				ret = ft_word_d(ret, info->env, &info->trash_lst);

			i++;
		}
	*index = i;
	*if_$ = check;
	return (ret);
}
/* -------------------- 3.Word function ----------------------------*/
char	*ft_word(char *buffer, t_shell *info)
{
	int		i;
	int		check;
	char	*tmp;

	i = 0;
	check = 0;
	tmp = NULL;
	if (info->token && is_here_doc(info->token))
	{
		while (!ft_isparsing_char(buffer[i]))
			i++;
		creat_and_add(tmp, buffer, WORD, i, info);
	}
	else
		tmp = analys_buffer(tmp, buffer, info, &i, &check);
	
	if (!tmp && check > 0)
		creat_and_add(tmp, NULL, WORD, 0, info);
	else
		creat_and_add(tmp, buffer, WORD, i, info);
	return (buffer + i);
}
