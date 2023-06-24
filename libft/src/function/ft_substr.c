/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossel <nrossel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:33:08 by nrossel           #+#    #+#             */
/*   Updated: 2023/05/24 10:35:41 by nrossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_substr(char *s, size_t start, size_t len, t_dlist **trash)
{
	size_t			i;
	char			*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (my_malloc(1, 1, trash));
	if (len > (ft_strlen(s + start)))
		len = (ft_strlen(s + start));
	str = my_malloc(len + 1, sizeof(char), trash);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	return (str);
}

/*int	main (int argc, char **argv)
{
	(void) argc;
	{
		char *str = argv[1];
		unsigned int i = ft_atoi(argv[2]);
		unsigned long long len = ft_atoi(argv[3]);
		char *ret = ft_substr(str, i, len);
		printf("%s", ret);
	}
}*/
