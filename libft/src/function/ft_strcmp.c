/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:57:32 by nrossel           #+#    #+#             */
/*   Updated: 2023/05/23 16:39:19 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int		i;
	int		len;
	char	*p1;
	char	*p2;

	i = 0;
	p1 = (char *) s1;
	p2 = (char *) s2;
	len = ft_strlen(p1);
	while (i < len)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}

/*int	main(int ac, char **av)
{
	int	res;

	(void) ac;
	res = ft_strcmp(av[1], av[2]);
	printf("%d\n", res);
	return (0);
}*/
