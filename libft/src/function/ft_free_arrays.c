/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 08:54:29 by nrossel           #+#    #+#             */
/*   Updated: 2023/05/23 16:37:14 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_free_arrays(char *str1, char *str2, char *error_msg)
{
	if (!str1 && !error_msg)
		return (1);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (error_msg != NULL)
		ft_exit(1, error_msg);
	return (0);
}
