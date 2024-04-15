/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:34:24 by vperez-f          #+#    #+#             */
/*   Updated: 2024/01/22 15:34:27 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkchr(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = ft_strlen(s1) - 1;
	while (s1[i] != '\0')
	{
		if (checkchr(set, s1[i]) == 1)
			i++;
		else
			break ;
	}
	if (i == (len + 1))
		return (res = ft_strdup(""));
	while (0 <= len)
	{
		if (checkchr(set, s1[len]) == 1)
			len--;
		else
			break ;
	}
	res = ft_substr(s1, i, (len - i) + 1);
	return (res);
}
