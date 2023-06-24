/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_delone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:51:02 by nrossel           #+#    #+#             */
/*   Updated: 2023/03/01 15:59:35 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"

void	ft_dlst_delone(t_node *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	lst->next = NULL;
	lst->prev = NULL;
	del(lst->data);
	free(lst);
}
