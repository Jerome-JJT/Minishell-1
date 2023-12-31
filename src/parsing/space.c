#include "../../minishell.h"

/* -------------------------- 1.Space function ------------------------------- */
char	*ft_space(char *str, t_tok **lst, t_dlist **trash)
{
	int		i;
	t_tok	*token;

	i = 0;
	while ((str[i] == ' ' || str[i] == '\t') && str[i] != '\0')
		i++;
	token = new_node(ft_strdup(" ", trash), SPACEE, trash);
	tok_addlst(lst, token);
	return (str + i);
}
