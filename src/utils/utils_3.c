#include "../../minishell.h"

/* -------------------- 1.Check print char ----------------------------*/
int	check_printchar(char c)
{
	if (ft_isprint(c) && !ft_isquote(c))
			return (1);
	return (0);
}

/* -------------------- 2.Check char parsing ----------------------------*/
int	ft_isparsing_char(char c)
{
	if (ft_isquote(c) || c == '|' || c == '<'
			|| c == '>' || c == ' ' || c == '\0')
			return (1);
	return (0);
}

/* -------------------- 3.Check tok ----------------------------*/
int	ft_isword(int token)
{
	if (token == WORD || token == S_QUOTE
			|| token == D_QUOTE)
			return (1);
	return (0);
}

/* -------------------- 4.Len quote str ----------------------------*/
int	ft_quotelen(char *str)
{
	int	i;

	i = 0;
	while (!ft_isquote(str[i]) && str[i])
		i++;
	return (i);
}

/* -------------------- 5.Check tok ----------------------------*/
void	creat_and_add(char *tmp, char *str, int type, int index, t_shell *info)
{
	t_tok	*token;

	if (!tmp)
	{
		if (type == S_QUOTE || type == D_QUOTE)
			token = new_node(ft_substr(str, 1, index - 1, &info->trash_lst), type, &info->trash_lst);
		else if (type == WORD)
			token = new_node(ft_substr(str, 0, index, &info->trash_lst), type, &info->trash_lst);
		else
			token = new_node(ft_substr(str, 0, index, &info->trash_lst), type, &info->trash_lst);
	}
	else
	{
		if (type == WORD)
			token = new_node(ft_substr(tmp, 0, ft_strlen(tmp), &info->trash_lst), type, &info->trash_lst);
		else
			token = new_node(ft_substr(tmp, 0, ft_quotelen(tmp), &info->trash_lst), type, &info->trash_lst);
	}
	tok_addlst(&info->token, token);
}