/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubblesort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:36:24 by nrossel           #+#    #+#             */
/*   Updated: 2023/02/27 11:46:58 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	bubblesort_int(int	*int_tab, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size -1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (int_tab[j] > int_tab[j + 1])
				ft_swap(&int_tab[j], &int_tab[j + 1]);
			j++;
		}
		i++;
	}
}
