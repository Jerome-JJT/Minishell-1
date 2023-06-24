/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:55:37 by nrossel           #+#    #+#             */
/*   Updated: 2023/05/24 09:51:31 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_calloc(size_t size, size_t type)
{
	void	*ptr;

	ptr = malloc(size * type);
	if (!ptr)
		return (ptr);
	ft_bzero(ptr, type * size);
	return (ptr);
}
