#include "../../minishell.h"


/* -------------------------- 1.Quote parsing ------------------------------- */
/* Check if quote = '' ou "" */
static char	*parse_quote(char *buff, t_shell *info)
{
	char	*str;

	str = buff;
	if (*str == '\'')
	{
		if (ft_checkquote(str, 1) != 0)
			return (NULL);
		str = ft_squote(str, info);
	}
	else if (*str == '\"')
	{
		if (ft_checkquote(str, 2) != 0)
			return (NULL);
		str = ft_dquote(str, info);
	}
	return (str);
}

/* --------------------- 2.Redirection parsing ------------------------------ */
/* Check if red = in ou out */
static char	*parse_red(char *buff, t_tok **lst, t_dlist **trash)
{
	char	*str;

	str = buff;
	if (*str == '<')
		str = red_in(str, lst, trash);
	else if (*str == '>')
		str = red_out(str, lst, trash);
	return (str);
}

/* -------------------------- 3.Quote parsing ------------------------------- */
static char	*sort_type(char *buff, t_shell *info)
{
	if (ft_isalnum(*buff) || (!ft_isparsing_char(*buff) && ft_isprint(*buff)))
		buff = ft_word(buff, info);
	else if ((*buff == '\'' || *buff == '\"'))
		buff = parse_quote(buff, info);
	else if (*buff == ' ' || *buff == '\t')
		buff = ft_space(buff, &info->token, &info->trash_lst);
	else if (*buff == '<' || *buff == '>')
		buff = parse_red(buff, &info->token, &info->trash_lst);
	else if (*buff == '|')
		buff = ft_pipe(buff, &info->token, &info->trash_lst);
	else
		buff++;
	return (buff);
}

/* -------------------------- 4.Char Sorting ------------------------------- */
int	ft_char_sort(char *buff, t_shell *info)
{
	if (*buff == '\t' || *buff == ' ')
	{
		while(*buff == '\t' || *buff == ' ')
			buff++;
	}
	while (*buff)
	{
		buff = sort_type(buff, info);
		if (buff == NULL)
		{
			g_errno = 1;
			return (1);
		}
	}
	return (0);
}

/* -------------------------- 5.Shell parsing ------------------------------- */
/* Main parsing : Tokenisation */
int	parse_shell(char *buff, t_shell *info, t_exec *exec)
{
	int	strlen;

	strlen = ft_strlen(buff);
	if (!buff)
		return (2);
	if (!*buff)
		return (3);
	if (ft_char_sort(buff, info) > 0)
		return (1);
	// print_token(&info->token, "before check");
	if (check_syntax(info, info->token, &info->trash_lst))
		return (2);
	// print_token(&info->token, "after check");
	pars_to_exec(info, exec, &info->trash_lst);
	return (0);
}
