#include "../../minishell.h"


/* -------------------------- 2.Quote parsing ------------------------------- */
/* Check if quote = '' ou "" */
static char	*parse_quote(char *buff, t_shell *info)
{
	char	*str;

	str = buff;
	if (ft_checkquote(str) != 0)
		return (NULL);
	if (*str == '\'')
		str = ft_squote(str, info);
	else if (*str == '\"')
		str = ft_dquote(str, info);
	return (str);
}

/* --------------------- 3.Redirection parsing ------------------------------ */
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

/* -------------------------- 1.Char Sorting ------------------------------- */
static int	ft_char_sort(char *buff, t_shell *info)
{
	t_tok	*tmp;
	int		strlen;

	strlen = ft_strlen(buff);
	while (*buff == ' ')
		buff++;
	while (*buff)
	{
		if (ft_isalnum(*buff) || (!ft_isparsing_char(*buff) && ft_isprint(*buff)))
			buff = ft_word(buff, info);
		else if ((*buff == '\'' || *buff == '\"'))
			buff = parse_quote(buff, info);
		else if (*buff == ' ')
			buff = ft_space(buff, &info->token, &info->trash_lst);
		else if (*buff == '<' || *buff == '>')
			buff = parse_red(buff, &info->token, &info->trash_lst);
		else if (*buff == '|')
			buff = ft_pipe(buff, &info->token, &info->trash_lst);
		else
			buff++;
		if (buff == NULL)
		{
			g_errno = 1;
			return (1);
		}
		if (*buff == '\0')
		{
			tmp = tok_lastnode(info->token);
			if (tmp->type == PIPE || (tmp->type == SPACEE && tmp->prev->type == PIPE))
			{
				while (strlen > 0)
				{
					printf("%d\n", strlen);
					buff--;
					strlen--;
				}
				free(buff);
				buff = readline(""BLUE">"RESET" ");
				add_history(buff);
			}
		}
	}
	return (0);
}

/* -------------------------- 4.Shell parsing ------------------------------- */
/* Main parsing : Tokenisation */
int	parse_shell(char *buff, t_shell *info, t_exec *exec)
{
	int	strlen;

	strlen = ft_strlen(buff);
	if (!buff)
		exit(0);
	if (!*buff)
		return (3);
	if (ft_char_sort(buff, info) > 0)
		return (1);
	if (check_syntax(info->token, &info->trash_lst))
		return (2);
	pars_to_exec(info, exec, &info->trash_lst);
	return (0);
}
