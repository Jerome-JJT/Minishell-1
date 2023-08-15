#include "../../minishell.h"

/* -------------------- 1.clear info node -----------------------*/
static void	clear_node(t_shell *info, t_list *node)
{
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
	int		j;
	int		check;
	t_list	*node;

	i = 0;
	check = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (!ft_isalpha(tab[i][j]) && tab[i][j] != '_')
			{
				ft_error_msg(1, tab[i], "unset", 0);
				break ;
			}
			j++;
		}
		node = find_var_env(info->env, tab[i++]);
		if (node)
		{
			clear_node(info, node);
			check++;
		}
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
