/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 08:38:13 by nrossel           #+#    #+#             */
/*   Updated: 2023/05/23 16:38:16 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
//#include <stdio.h>

int	ft_nbrlen_b(unsigned int nbr)
{
	int	i;

	i = 0;
	while (nbr > 0)
	{
		nbr /= 2;
		i++;
	}
	return (i);
}

// int main(int ac, char **av)
// {
	// (void) ac;
	// int nbr = atoi(av[1]);
	// int ret = ft_nbrlen_b(nbr);
	// printf("%d", ret);
// }