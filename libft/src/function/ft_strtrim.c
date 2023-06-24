/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:05:04 by nrossel           #+#    #+#             */
/*   Updated: 2023/05/23 16:40:11 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	isset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set, t_dlist **trash_lst)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	strlen;
	char	*str;

	i = 0;
	k = 0;
	while (isset(s1[i], set))
		i++;
	j = ft_strlen(s1) - 1;
	while (isset(s1[j], set))
	{
		k++;
		j--;
	}
	strlen = ft_strlen(s1) - (i + k);
	str = ft_substr((char *)s1, i, strlen, trash_lst);
	if (!str)
		return (NULL);
	return (str);
}

/*int	main (int argc, char **argv)
{
	(void) argc;
	{
		char *str1 = argv[1];
		char *str2 = argv[2];
		char *ret = ft_strtrim(str1, str2);
		printf("%s", ret);
	}
}*/
