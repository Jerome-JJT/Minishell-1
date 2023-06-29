#include "../../minishell.h"

/* -------------------------- 1.Join str node_tmp ------------------------------- */
static void	strjoin_node_tmp(t_tok *dest, t_tok *src, t_dlist **trash)
{
	dest->tok = ft_strjoin(dest->tok, src->tok, trash);
	dest->next = src->next;
	src->next = NULL;
}

/* -------------------------- 2.Syntax ------------------------------- */
int	check_syntax(t_tok *lst, t_dlist **trash)
{
	int		i;
	int		in;
	t_tok	*node;
	t_tok	*node_tmp;

	i = 0;
	node = lst;
	in = 0;
	// print_token(&lst, "check_syntax");
	while (node != NULL)
	{
		node_tmp = node;
		if (node->type == RED_IN || node->type == RED_OUT
			|| node->type == APPEND)
		{
			node_tmp = node_tmp->next;
			if (!node_tmp)
				return (ft_error_msg(258, NULL));
			else if (node_tmp->type == SPACE)
				node_tmp = node_tmp->next;
			if (!node_tmp)
				return (ft_error_msg(258, NULL));
			else if (node_tmp->type != WORD)
				return (ft_error_msg(258, node_tmp->tok));
			else if (ft_isword(node_tmp->type) == 1)
			{
				if (node->type == RED_IN || node->type == APPEND)
				{
					fprintf(stderr, "%s\n", node_tmp->tok);
					if (open(node_tmp->tok, O_RDONLY) < 0)
						return (ft_error_msg(1, node_tmp->tok));
				}
				else
				{
					if (access(node_tmp->tok, F_OK) == 0)
						unlink(node_tmp->tok);
					if (open((node_tmp->tok), O_CREAT | O_WRONLY, 0777) < 0)
						fprintf(stderr, "Outfile opening fail\n");
				}
			}
			node = node_tmp->next;
		}
		else if (node->type == H_D)
		{
			node_tmp = node_tmp->next;
			if (!node_tmp)
				return (ft_error_msg(258, NULL));
			if (node_tmp->type == SPACE)
				node_tmp = node_tmp->next;
			if (!node_tmp)
				return (ft_error_msg(258, NULL));
			else if (node_tmp->type != WORD)
				return (ft_error_msg(258, node_tmp->tok));
			node = node_tmp->next;
		}
		else if (node->type == PIPE && i == 0)
			return (ft_error_msg(258, node->tok));
		else if (ft_isword(node->type) && node->next != NULL)
		{
			if (ft_isword(node->next->type))
				strjoin_node_tmp(node, node->next, trash);
			else
				node = node->next;
		}
		else
			node = node->next;
		i++;
	}
	return (0);
}

// if node_tmp_type == SPACE
// 	s++;
// else if node_tmp_type == RED_IN
// 	while (node_tmp_type == SPACE)
// 		if (node_tmp_type == NULL) /* ---------- */
// 			return (1) -->> bash: syntax error near unexpected token `newline
// 	if (node_tmp_type != WORD)
// 		return (1) -->> bash: syntax error near unexpected token `s
// 	else (node_tmp_type == WORD)
// 		in = open(s, O_RDONLY)
// 		if (in < 0)
// 			return (2) -->> bash: salut: No such file or directory

// else if node_tmp_type == HERE_DOC
// 	while (node_tmp_type == SPACE)
// 		if (node_tmp_type == NULL)/* ---------- */
// 			return (1) -->> bash: syntax error near unexpected token `newline
// 	if (node_tmp_type != WORD)
// 		return (1) -->> bash: syntax error near unexpected token `s

// else if node_tmp_type == RED_OUT
// 	while (node_tmp_type == SPACE)
// 		if (node_tmp_type == NULL)/* ---------- */
// 			return (1) -->> bash: syntax error near unexpected token `newline
// 	if (node_tmp_type != WORD)
// 		return (1) -->> bash: syntax error near unexpected token `s

// else if node_tmp_type == APPEND
// 	while (node_tmp_type == SPACE)
// 		if (node_tmp_type == NULL)/* ---------- */
// 			return (1) -->> bash: syntax error near unexpected token `newline
// 	if (node_tmp_type != WORD)
// 		return (1) -->> bash: syntax error near unexpected token `s

// else if node_tmp_type == PIPE
// 	if PIPE == first_node_tmp
// 		return (1) -->> bash: syntax error near unexpected token `|
