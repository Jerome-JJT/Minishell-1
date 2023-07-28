#include "../../minishell.h"

/* -------------------------- 1.Join str node_tmp ------------------------------- */
static void	strjoin_tok_node(t_tok *dest, t_tok *src, t_dlist **trash)
{
	dest->tok = ft_strjoin(dest->tok, src->tok, trash);
	dest->next = src->next;
	src->next = NULL;
}

/* -------------------------- 2.If token is in_out_append ------------------------------- */
static int	in_out_append(t_tok **node)
{
	t_tok	*tmp;

	tmp = (*node)->next;
	if (!tmp)
		return (ft_error_msg(258, NULL));
	else if (tmp->type == SPACE)
	{
		tmp = tmp->next;
		if (!tmp)
			return (ft_error_msg(258, NULL));
	}
	if (tmp->type != WORD)
		return (ft_error_msg(258, tmp->tok));
	else if (ft_isword(tmp->type) == 1)
	{
		if ((*node)->type == RED_IN || (*node)->type == APPEND)
		{
			if (open(tmp->tok, O_RDWR) < 0) // -->> A changer selon le type de permissions accordées de base au fichier
				return (ft_error_msg(1, tmp->tok));
		}
		else
		{
			if (access(tmp->tok, F_OK) == 0)
				unlink(tmp->tok);
			if (open((tmp->tok), O_CREAT | O_WRONLY, 0777) < 0)
				perror("Opening outfile error");
		}
		(*node) = tmp->next;
	}
	return (0);
}

/* -------------------------- 3.If token is heredoc ------------------------------- */
static int	heredoc(t_tok *node)
{
	t_tok	*tmp;

	tmp = node->next;
	if (!tmp)
		return (ft_error_msg(258, NULL));
	if (tmp->type == SPACE)
		tmp = tmp->next;
	if (!tmp)
		return (ft_error_msg(258, NULL));
	else if (tmp->type != WORD)
		return (ft_error_msg(258, tmp->tok));
	node = tmp->next;
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
			&& found_char((*current_node)->tok, ' ') > 0)
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

	node = lst;
	while (node != NULL)
	{
		// printf("%s\n", node->tok); // -----> ***
		if (node->type == PIPE && node->prev == NULL)
			return (ft_error_msg(258, node->tok));
		else if (node->type == RED_IN || node->type == RED_OUT
			|| node->type == APPEND)
		{
			if (in_out_append(&node) > 0)
				return (1);
		}
		else if (node->type == H_D)
		{
			if (heredoc(node) > 0)
				return (1);
		}
		else if (ft_isword(node->type))
			word(&node, node->next, trash);
		else
			node = node->next;
	}
	return (0);
}
