#include "../../minishell.h"

void	print_tab(char **tab, char *ft)
{
	int	i;

	i = 0;
	printf("%s\n", ft);
	printf("----------------------------------------------------------------\n");
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("----------------------------------------------------------------\n\n\n");
}

void	print_list(t_env *lst, char *ft)
{
	t_list	*node;

	node = lst->head;
	printf("%s\n", ft);
	printf("----------------------------------------------------------------\n");
	printf("%zu\n", lst->len);
	while (node != NULL)
	{
		printf("Data:		%p\n", node->data);
		printf("Variable:	%s\n", node->variable);
		printf("Valeur:		%s\n", node->valeur);
		node = node->next;
	}
	printf("----------------------------------------------------------------\n");
}

void	print_token(t_tok **lst, char *ft)
{
	t_tok	*node;

	node = *lst;
	printf("%s\n", ft);
	printf("|----------------------------|\n");
	while (node != NULL)
	{
		printf("Token:	%s Type: %u N°: %d\n", node->tok, node->type, node->len);
		if (node->next != NULL)
			printf("|----------------------------|\n");
		node = node->next;
	}
	printf("|----------------------------|\n");
}

void	test(char *str, char *fonction)
{
	static int	i;

	printf("---->> %s\n", fonction);
	printf("%d.%s\n", i, str);
	i++;
}

void	print_node(t_tok *node)
{
	printf("Token:	%s\nType:	%d\n", node->tok, node->type);
}

void	print_parsing(t_exec *exec, char *ft)
{
	printf("%s\n", ft);
	print_tab(exec->heredoc, "test heredoc");
	print_tab(exec->tab_cmd, "test tab_cmd");
	print_tab(exec->redi_infile, "test red_in");
	print_tab(exec->redi_outfile, "test red_out");
}