#include "../../minishell.h"

/* ------------------------- 1.Print env ------------------------------*/
static void	print_env(t_env *env)
{
	t_list	*node;

	node = env->head;
	while (node != NULL)
	{
		if (env->head->if_var_env == 1)
			printf("%s=%s\n", node->variable, node->valeur);
		node = node->next;
	}
	g_errno = 0;
}

/* ------------------------- 2.Env avec args ------------------------------*/
static void	env_with_arg(t_shell *info, char **arg)
{
	if (ft_strncmp(*arg, "env", 4) == 0)
	{
		while (ft_strncmp(*arg, "env", 4) == 0 && *arg != NULL)
			arg++;
		// fprintf(stderr, "*arg = %s\n", *arg);
		if (arg != NULL)
		{
				// fprintf(stderr, "ici ?\n");
				ft_error_msg(127, *arg, "env", 0);
				return ;
		}
		print_env(info->env);
		g_errno = 0;
	}
	else if (ft_strncmp(*arg, "/", 1) == 0 && access(*info->arg, F_OK))
	{
		if (access(*arg, W_OK) != 0)
			ft_error_msg(126, *arg, "env", 0);
	}
	else
		ft_error_msg(127, *arg, "env", 0);
}

/* ------------------------- 3.Fonction env ------------------------------*/
void	env_minishell(t_shell *info, char *arg)
{
	t_list	*node;
	char	**tab_arg;

	if (!info->env->head)
	{
		printf("No minishell environment\n");
		return ;
	}
	node = info->env->head;
	if (arg)
	{
		tab_arg = ft_split(arg, ' ', &info->trash_lst);
		env_with_arg(info, tab_arg);
	}
	else
	{
		while (node != NULL)
		{
			if (node->if_var_env == 1)
				printf("%s=%s\n", node->variable, node->valeur);
			node = node->next;
		}
		g_errno = 0;
	}
}

/*
Test déjà effectué:
--------------------------------------------|
1.env = liste variable d'environnement
2.env env = idem 1
3.env env env = idem 1
4.
5.env 123 = 123: no file (error 127)
6.env abc = abc: no file (error 127)
7.env /bin = no access (error 126)
8.env /bin -> env $? -> env $? = error 126 puis 127
9.env $?abc -> à corriger /!\







*/
