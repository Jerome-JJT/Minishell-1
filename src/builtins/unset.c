#include "../../minishell.h"

/* -------------------- 1.clear info node -----------------------*/
static void	clear_node(t_shell *info, t_list *node)
{
	// printf("node->next:	%p\n", node->next);
	// printf("node->prev:	%p\n", node->prev);
	// printf("node->variable:	%s\n", node->variable);
	if (!node->prev)
	{
		node->next->prev = NULL;
		info->env->head = node->next;
	}
	else
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
	}
	node->valeur = NULL;
	node->variable = NULL;
	node->next = NULL;
	node = NULL;
	info->env->len--;
}

/* -------------------- 2.analyze arg unset -----------------------*/
static int	analyze_arg_unset(char **tab, t_shell *info)
{
	int		i;
	int		check;
	t_list	*node;

	i = 0;
	check = 0;
	while (tab[i])
	{
		// printf("tab[%d] = %s\n", i, tab[i]);
		if (ft_isalpha(tab[i][0]) || tab[i][0] == '_')
		{
			node = find_var_env(info->env, tab[i++]);
			// printf("ptr node -> %p\n", node);
			if (node)
			{
				// print_list(info->env, "unset", 2);
				// printf("ici ?\n");
				clear_node(info, node);
				check++;
			}
		}
		else
			ft_error_msg(1, tab[i++], "unset");
	}
	return (check);
}

/* -------------------- 1.Main function unset -----------------------*/
int	unset_minishell(t_shell *info, char *arg)
{
	char	**tab;
	int		check;

	if (!arg || !*arg)
		return (0);
	if (arg[0] == '\"')
		remove_quote(arg, '\"');
	check = 0;
	tab = ft_split(arg, ' ', &info->trash_lst);
	if (tab)
		check = analyze_arg_unset(tab, info);
	if (check != 0)
		return (1);
	return (0);
}
