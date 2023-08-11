#include "../../minishell.h"

void	print_tab(char **tab, char *ft)
{
	// int	i;

	// i = 0;
	printf("%s\n", ft);
	printf("----------------------------------------------------------------\n");
	while (1)
	{
		printf("-->> %s|\n", *tab);
		if (*tab == NULL)
			break;
		tab++;
	}
	printf("----------------------------------------------------------------\n\n\n");
}

void	print_list(t_env *lst, char *ft, int info)
{
	t_list	*node;

	node = lst->head;
	printf("%s\n", ft);
	printf("----------------------------------------------------------------\n");
	printf("%zu\n", lst->len);
	while (node != NULL)
	{
		if (info > 0)
		{
			printf("Variable:	"BLUE"%s"RESET"\n", node->variable);
			printf("Valeur:		"BLUE"%s"RESET"\n", node->valeur);
		}
		if (info > 1)
			printf("Adresse prev <- current -> next: "RED"%p"RESET"		<-		%p		->		"GREEN"%p"RESET"\n", node->prev, node, node->next);
		if (info > 2)
			printf("Data:		%p\n", node->data);
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
	if (*exec->heredoc)
		print_tab(exec->heredoc, "test heredoc");
	if(*exec->tab_cmd)
		print_tab(exec->tab_cmd, "test tab_cmd");
	if (*exec->redi_infile)
		print_tab(exec->redi_infile, "test red_in");
	if (*exec->redi_outfile)
		print_tab(exec->redi_outfile, "test red_out");
	if (*exec->append)
		print_tab(exec->append, "test append");
}

void	print_trash(t_dlist **trash)
{
	t_node *tmp;

	tmp = (*trash)->head;
	while (tmp)
	{
		printf("adresse node: %p -> adresse stockée: %p -> valeur: %s\n", tmp, tmp->data, (char *)tmp->data);
		tmp = tmp->next;
	}
}