/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 08:55:58 by nrossel           #+#    #+#             */
/*   Updated: 2023/05/23 16:38:29 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_power(int nbr, unsigned int power)
{
	unsigned int	i;
	long long		nb;

	i = 0;
	nb = (long long)nbr;
	if (power == 0)
	{
		if (nb < 0)
			return (-1);
		else
			return (1);
	}
	else if (power == 1)
		return (nb);
	while (++i != power)
		nb *= nbr;
	if (nbr < 0)
		nb = -nb;
	return (nb);
}

// int main (int ac, char **av)
// {
	// (void) ac;
	// int nbr = ft_power(atoi(av[1]), atoi(av[2]));
	// ft_printf("%d", nbr);
	// 
// }