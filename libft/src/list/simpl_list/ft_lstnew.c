/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:32:17 by nrossel           #+#    #+#             */
/*   Updated: 2023/05/23 16:19:33 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"

t_list	*ft_lstnew(void *data, t_dlist **trash_lst)
{
	t_list	*list;

	list = my_malloc(0, sizeof(t_list), trash_lst);
	if (!list)
		return (NULL);
	list->data = data;
	list->next = NULL;
	return (list);
}
