#include "../../minishell.h"

/* ------------------- 1. Str to node --------------------*/
void	str_to_node(char *str, t_list *node, t_shell *info, int first_time)
{
	char	**tab;
	int		egal;
	t_list	*tmp;

	tmp = NULL;
	egal = found_char(str, '=');
	if (egal > 0)
	{
		tab = split_arg(str, egal, &info->trash_lst);
		if (!first_time)
			tmp = find_var_env(info->env, tab[0], 1);
		if (!tmp)
			fill_node(node, ft_strdup(tab[0], &info->trash_lst),
				ft_strdup(tab[1], &info->trash_lst), 1);
		else
			fill_node(tmp, ft_strdup(tab[0], &info->trash_lst),
				ft_strdup(tab[1], &info->trash_lst), 1);

	}
	else
		fill_node(node, ft_strdup(str, &info->trash_lst), NULL, 0);
}

/* -------------------- 2. Fill node -----------------------*/
void	fill_node(t_list *node, char *s1, char *s2, int if_var)
{
	node->variable = s1;
	node->valeur = s2;
	node->if_var_env = if_var;
}

/* -------------------- 3.Find Variable env. -----------------------*/
t_list	*find_var_env(t_env *env, char *var, int if_dd)
{
	t_list	*node;

	node = env->head;
	if (if_dd == 0)
		var++;
	while (node != NULL)
	{
		if (var[ft_strlen(var) - 1] == '=')
		{
			if (ft_strncmp(var, node->variable,
					ft_strlen(var) - 2) == 0)
				return (node);
		}
		else
		{
			if (ft_strlen(var) == ft_strlen(node->variable))
			{
				if (ft_strncmp(var, node->variable,
						ft_strlen(var)) == 0)
					return (node);
			}
		}
		node = node->next;
	}
	return (NULL);
}

/* ---------------------------- 4.list "env" to tab --------------------------------*/
char	**lst_to_tab(t_env *lst, t_dlist **trash)
{
	char		**tab;
	t_list		*node;
	size_t		i;
	int			var;
	int			val;

	tab = my_malloc((lst->len + 1), sizeof(char *), trash);
	if (!tab)
		return (NULL);
	node = lst->head;
	i = 0;
	while (node != NULL && node->variable != NULL)
	{
		if (*node->valeur)
		{
			var = ft_strlen(node->variable) + 1;
			val = ft_strlen(node->valeur) + 1;
			tab[i] = my_malloc((var + val), sizeof(char), trash);
			if (!tab[i])
				return (NULL);
			tab[i] = ft_strjoin(node->variable, "=", trash);
			tab[i] = ft_strjoin(tab[i], node->valeur, trash);
		}
		else if (!*node->valeur && ft_isupper(*node->variable))
			tab[i] = ft_strjoin(node->variable, "=", trash);
		else
			tab[i] = ft_strdup(node->variable, trash);
		i++;
		node = node->next;
	}
	// print_tab(tab, "lst_to_tab");
	return (tab);
}

/* ------------------------- 5. Tab to list ---------------------------*/
void	tab_to_lst(t_shell *info, char **envp)
{
	int		i;
	t_list	*node;

	i = 0;
	while (envp[i])
	{
		node = ft_dlst_newcontent(NULL, &info->trash_lst);
		str_to_node(envp[i], node, info, 1);
		ft_dlst_addback(&info->env, node);
		node = NULL;
		i++;
	}
}
