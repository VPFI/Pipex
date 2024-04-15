/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:32:26 by vperez-f          #+#    #+#             */
/*   Updated: 2024/01/17 14:37:15 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	char	*ans;
	size_t	oglen;
	size_t	i;
	size_t	j;

	i = 0;
	oglen = len;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && 0 < len)
	{
		j = 0;
		while (str[i + j] != '\0' && str[i + j] == to_find[j] && 0 < len)
		{
			if (to_find[j + 1] == '\0')
				return (ans = (char *)&str[i]);
			j++;
			len--;
		}
		i++;
		len = oglen - i;
	}
	return (NULL);
}
/*
int	main ()
{
	char	a[] = "asdafght";
	int		i = strlen(a);
	while (0 <= i)
	{
		printf("%i || O:%s --- ", i, strnstr(a, "fght", i));
		printf("ft:%s\n", ft_strnstr(a, "fght", i));
		i--;
	}
}*/
