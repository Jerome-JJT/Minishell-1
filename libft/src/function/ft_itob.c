/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 08:25:33 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/12 13:12:04 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
#include <stdio.h>

int	ft_itob(int nbr)
{
	unsigned long long	d;
	int					len;
	char				*b;

	b = NULL;
	len = ft_nbrlen_b(nbr);
	d = 0;
	b = (char *)malloc((len + 1) * sizeof(char));
	if (!b)
		return (0);
	len--;
	while (len >= 0)
	{
		b[len] = (nbr % 2) + '0';
		nbr /= 2;
		len--;
	}
	d = ft_atoll(b);
	free(b);
	return (d);
}

/*nbr max = 1023*/

// int main(int ac, char **av)
// {
	// (void) ac;
	// int b = atoi(av[1]);
	// int decimal = ft_btoi(b);
	// printf("%d", decimal);
// }