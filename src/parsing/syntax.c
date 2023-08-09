#include "../../minishell.h"

/* -------------------------- 1.if token is pipe ------------------------------- */
static int	check_pipe(t_tok **node)
{
	t_tok	*tmp;

	tmp = *node;
	*node = (*node)->next;
	if (!tmp->prev || tmp->prev->type == PIPE)
		return (ft_error_msg(258, tmp->tok));
	else if (tmp->prev->type == SPACEE)
	{
		if (type_is_sep(tmp->prev->prev->type))
			return (ft_error_msg(258, tmp->tok));
	}
	return (0);
}

/* -------------------------- 2.If token is in, out or append ------------------------------- */
static int	in_out_append(t_tok **node)
{
	t_tok	*tmp;

	tmp = (*node)->next;
	if (!tmp)
		return (ft_error_msg(258, NULL));
	else if (tmp->type == SPACEE)
	{
		tmp = tmp->next;
		if (!tmp)
			return (ft_error_msg(258, NULL));
	}
	if (tmp->type != WORD)
		return (ft_error_msg(258, tmp->tok));
	else if (ft_isword(tmp->type) == 1)
	{
		if ((*node)->type == RED_IN)
		{
			if (open(tmp->tok, O_RDWR) < 0)
				return (ft_error_msg(1, tmp->tok));
		}
		else if ((*node)->type == RED_OUT)
		{
			if (access(tmp->tok, F_OK) == 0)
				unlink(tmp->tok);
			if (open(tmp->tok, O_WRONLY | O_CREAT | O_TRUNC, 0644) < 0)
				return (ft_error_msg(1, tmp->tok));
		}
		(*node) = tmp->next;
	}
	return (0);
}

/* -------------------------- 3.If token is heredoc ------------------------------- */
static int	heredoc(t_tok **node)
{
	t_tok	*tmp;

	tmp = (*node)->next;
	if (!tmp)
		return (ft_error_msg(258, NULL));
	else if (tmp->type == SPACEE)
		tmp = tmp->next;
	if (!tmp)
		return (ft_error_msg(258, NULL));
	else if (tmp->type != WORD)
		return (ft_error_msg(258, tmp->tok));
	(*node) = tmp->next;
	return (0);
}

/* -------------------------- 4.If token is quotes or word ------------------------------- */
static void	word(t_tok **current_node, t_tok *next_node, t_dlist **trash)
{
	if ((ft_isword((*current_node)->type) && next_node != NULL)
				&& ft_isword(next_node->type))
	{
		if (ft_strncmp("\"", (*current_node)->tok, 1) != 0)
			(*current_node)->tok = ft_strjoin("\"", (*current_node)->tok, trash);
		strjoin_tok_node((*current_node), next_node, trash);
		if ((*current_node)->next == NULL || !ft_isword((*current_node)->next->type))
		{
			(*current_node)->tok = ft_strjoin((*current_node)->tok, "\"", trash);
			*current_node = next_node;
		}
	}
	else if (((*current_node)->type == S_QUOTE || (*current_node)->type == D_QUOTE)
			&& found_char((*current_node)->tok, ' ' > 0))
	{
		(*current_node)->tok = ft_strjoin("\"", (*current_node)->tok, trash);
		(*current_node)->tok = ft_strjoin((*current_node)->tok, "\"", trash);
		(*current_node) = next_node;
	}
	else
		(*current_node) = next_node;
}

/* -------------------------- 5.Syntax ------------------------------- */
int	check_syntax(t_tok *lst, t_dlist **trash)
{
	t_tok	*node;
	int		check;

	node = lst;
	check = 0;
	while (node != NULL)
	{
		if (node->type == PIPE)
			check = (check_pipe(&node));
		else if (node->type == RED_IN || node->type == RED_OUT
			|| node->type == APPEND)
			check = (in_out_append(&node));
		else if (node->type == H_D)
			check = (heredoc(&node));
		else if (ft_isword(node->type))
			word(&node, node->next, trash);
		else
			node = node->next;
		if (check > 0)
		{
			return (1);
		}
	}
	return (0);
}
