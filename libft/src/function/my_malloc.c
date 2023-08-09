/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:54:29 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/09 16:54:34 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*my_malloc(size_t size, size_t type, t_dlist **trash)
{
	void	*ptr;
	t_list	*new;

	ptr = ft_calloc(size, type);
	if (!ptr)
		return (NULL);
	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (NULL);
	new->data = ptr;
	ft_dlst_addback(trash, new);
	return (ptr);
}
