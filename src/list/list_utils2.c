#include "../../minishell.h"

/* -------------------------- 1.New token node ------------------------------- */
t_tok	*new_node(char *str, int token, t_dlist **trash)
{
	t_tok	*new;

	new = my_malloc(1, sizeof(t_tok), trash);
	if (!new)
		return (NULL);
	if (!str)
	{
		// printf("check 3\n");
		new->tok = NULL;
	}
	else
	{
		// printf("check 4\n");
		new->tok = str;
	}
	new->type = token;
	new->next = 0;
	new->prev = 0;
	new->len =	0;
	return (new);
}

/* ------------------- 2.Last tok lst --------------------*/
t_tok	*tok_lastnode(t_tok *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}