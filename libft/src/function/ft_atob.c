/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 08:24:52 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/12 13:13:02 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
//#include <stdio.h>

int	ft_atob(char *str)
{
	long long	decimal;
	int			len;
	int			bin;
	char		*bin_str;

	decimal = ft_atoll(str);
	len = ft_nbrlen_b(decimal);
	bin = 0;
	bin_str = NULL;
	bin_str = malloc((len + 1) * sizeof(char));
	if (!bin_str)
		return (0);
	bin_str[len] = '\0';
	len--;
	while (decimal > 0)
	{
		bin_str[len] = (decimal % 2) + '0';
		decimal /= 2;
		len--;
	}
	bin = ft_atoll(bin_str);
	free(bin_str);
	return (bin);
}
// 
// int main (int ac, char **av)
// {
	// (void) ac;
	// int binaire = ft_atob(av[1]);
	// printf("%d", binaire);
// }