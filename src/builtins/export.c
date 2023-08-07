#include "../../minishell.h"

/* -------------------------- 1.Print export -------------------------------*/
static void	print_export(char **var)
{
	int	i;
	int	j;

	i = -1;
	while (var[i])
	{
		if (found_char(var[i], '='))
		{
			j = 1;
			printf("declare -x ");
			while (var[i][j - 1] != '=')
				printf("%c", var[i][j++]);
			printf("\"");
			while (var[i][j])
				printf("%c", var[i][j++]);
			printf("\"\n");
		}
		else
		{
			j = 0;
			printf("declare -x ");
			while(var[i][j])
				printf("%c", var[i][j++ - 1]);
			printf("\n");
		}
		i++;
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

/* ------------------------- 5.Fonction export ------------------------------*/
void	export_minishell(t_shell *info, char **arg)
{
	t_list	*node;
	int		i;

	i = 0;
	if (!*arg)
		export_no_args(info);
	else
	{
		while (arg[i])
		{
			arg[i] = remove_quote(arg[i]);
			if (!ft_isalpha(arg[i][0])|| arg[i][0] == '$')
				printf("minishell: export: `%s': not a valid identifier\n",
					arg[i]);
			else
			{
				node = find_var_env(info->env, arg[i], 1);
				if (!node)
				{
					node = ft_dlst_newcontent(NULL, &info->trash_lst);
					str_to_node(arg[i], node, info, 0);
					ft_dlst_addback(&info->env, node);
				}
				else
					fill_node(node, node->variable, ft_strrchr(arg[i], '=') + 1, 1);
			}
			i++;
		}	
	}
}
