#include "../../minishell.h"

/* -------------------------- 1.Print export -------------------------------*/
static void	print_export(char **var)
{
	int	i;
	int	j;

	i = -1;
	while (var[++i])
	{
		j = 0;
		if (found_char(var[i], '='))
		{
			printf("declare -x ");
			while (var[i][j] != '=')
				printf("%c", var[i][j++]);
			j++;
			printf("=\"");
			while (var[i][j])
				printf("%c", var[i][j++]);
			printf("\"\n");
		}
		else
		{
			printf("declare -x ");
			while(var[i][j])
				printf("%c", var[i][j++]);
			printf("\n");
		}
	}
}

/* -------------------- 2. Tri apha tab -----------------------*/
static void	ft_trialpha(char **env)
{
	int		i;
	int		j;
	char	**var;

	i = 0;
	var = env;
	while (i < ft_tabsize(env))
	{
		j = 0;
		while (var[j])
		{
			if (var[j + 1] && ft_strcmp(var[j], var[j + 1]) > -1)
				ft_strswap(&var[j], &var[j + 1]);
			j++;
		}
		i++;
	}
	print_export(var);
}

/* -------------------- 3.Export without args -------------------------*/
static void	export_no_args(t_shell *info)
{
	char	**env;

	env = lst_to_tab(info->env, &info->trash_lst);
	ft_trialpha(env);
}

/* ------------------------- 4.Fonction export ------------------------------*/
int	export_minishell(t_shell *info, char *arg)
{
	t_list	*node;
	char	**tab;
	char	*tmp;
	int		i;

	i = 0;
	if (!arg)
	{
		export_no_args(info);
		return (0);
	}
	else
	{
		tab = ft_split(arg, ' ', &info->trash_lst);
		while (tab[i])
		{
			if (tab[i][0] == '\"')
				remove_quote(tab[i], '\"');
			// fprintf(stderr, "export tmp -> %s\n", tmp);
			// printf("tab[%d] = %s\n", i, tab[i]);
			if (!ft_isalpha(tab[i][0]) && tab[i][0] != '_')
				printf("minishell: export: `%s': not a valid identifier\n", tab[i]);
			else
			{
				node = find_var_env(info->env, tab[i]);
				if (!node)
				{
					node = ft_dlst_newcontent(NULL, &info->trash_lst);
					str_to_node(tab[i], node, info, 0);
					ft_dlst_addback(&info->env, node);
				}
				else
				{
					if (found_char(tab[i], '='))
					{
						tmp = ft_strrchr(tab[i], '=');
						// printf("%p\n%s\n", &tmp, tmp);
						if (!node->valeur && !tmp)
							fill_node(node, node->variable, ft_strdup(tmp, &info->trash_lst), 1);
						else
							fill_node(node, node->variable,  ft_strdup(tmp + 1, &info->trash_lst), 1);
					}
				}
			}
			i++;
		}	
	}
	return (1);
}
