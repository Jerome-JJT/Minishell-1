/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:04:23 by nrossel           #+#    #+#             */
/*   Updated: 2023/05/29 14:51:32 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* -------------------------- 1.New token node ------------------------------- */
t_tok	*new_node(char *str, int token, t_dlist **trash)
{
	t_tok	*new;

	new = my_malloc(1, sizeof(t_tok), trash);
	if (!new)
		return (NULL);
	new->tok = str;
	new->type = token;
	new->next = 0;
	new->prev = 0;
	new->len =	0;
	return (new);
}

/* -------------------------- 2.Add token node to lst ------------------------------- */
void	tok_addlst(t_tok **lst, t_tok *token)
{
	t_tok	*ptr;

	ptr = *lst;
	if (!token)
		return ;
	if (!*lst)
	{
		*lst = token;
		token->len++;
		return ;
	}
	ptr->len++;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		ptr->len++;
	}
	ptr->next = token;
	token->prev = ptr;
	token->len++;
}

/* -------------------------- 3.Clear token lst ------------------------------- */
void	tok_clearlst(t_tok **lst)
{
	t_tok	*ptr;

	if (!*lst)
		return ;
	ptr = *lst;
	while (*lst != NULL)
	{
		ptr = (*lst)->next;
		free((*lst)->tok);
		free(*lst);
		*lst = ptr;
	}
	*lst = NULL;
}

/* -------------------------- 3.Len token lst ------------------------------- */
static int	len_tokenlst(t_tok *token)
{
	int		i;
	t_tok	*tmp;

	if (!token)
		return (0);
	i = 0;
	tmp = token;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

/* -------------------------- 4.lst token to **tab ------------------------------- */
char    **tokenlst_to_tab(t_tok *token, t_dlist **trash)
{
	int		i;
	t_tok	*tmp;
	char	**tab;

	if (!token)
		return (NULL);
	i = len_tokenlst(token);
	tmp = token;
	tab = my_malloc((i + 1), (sizeof(char *)), trash);
	if (!tab)
		return (NULL);
	tab[i] = NULL;
	i = 0;
	while (tmp)
	{
		tab[i] = tmp->tok;
		i++;
		tmp = tmp->next;
	}
	return (tab);
}