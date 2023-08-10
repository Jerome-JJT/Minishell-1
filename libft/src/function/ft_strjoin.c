/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:02:02 by nrossel           #+#    #+#             */
/*   Updated: 2023/08/10 15:57:25 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static char	*ft_cpy(char *str, char *s1, char *s2, size_t len_max)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i] && i < len_max)
		{
			str[i] = s1[i];
			i++;
		}
	}
	if (s2)
	{
		while (s2[j] && j < len_max)
		{
			str[i + j] = s2[j];
			j++;
		}
	}
	str[i + j] = 0;
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2, t_dlist **trash)
{
	size_t		len_max;
	char		*str;

	if (!s1 && !s2)
		return (NULL);
	len_max = ((ft_strlen(s1) + ft_strlen(s2)) + 1);
	str = my_malloc(len_max, sizeof(char), trash);
	if (!str)
		return (NULL);
	ft_cpy(str, (char *)s1, (char *)s2, len_max);
	if (!*str)
		return (NULL);
	return (str);
}

