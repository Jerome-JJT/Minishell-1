#include "../../minishell.h"

/* ------------------- 1.Last tok lst --------------------*/
t_tok	*tok_lastnode(t_tok *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}