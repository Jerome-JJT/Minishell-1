#include "../../minishell.h"

static void	clear_node(t_shell *info, t_list *node)
{
	if (node->next)
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}
	else
	{
		node->prev->next = NULL;
		info->env->tail = node->prev;
	}
	node->valeur = NULL;
	node->variable = NULL;
	info->env->len--;
}

int	unset_minishell(t_shell *info, char *arg)
{
	t_list	*node;
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(arg, ' ', &info->trash_lst);
	if (tab)
	{
		while (tab[i])
		{
			node = find_var_env(info->env, tab[i++], 1);
			if (node != NULL)
			{
				clear_node(info, node);
				return (1);
			}
		}
	}
	return (0);
}
