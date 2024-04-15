/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:55:34 by vperez-f          #+#    #+#             */
/*   Updated: 2024/01/25 18:34:36 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	s_len;
	size_t			i;

	i = 0;
	s_len = ft_strlen(s);
	if (*s == '\0')
		return (ft_strdup(""));
	if (s_len < start)
	{
		len = 0;
		start = 0;
	}
	else if ((s_len - start) < len)
		len = (s_len - start);
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (s[start + i] != '\0' && len-- > 0)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
/*
int main(void)
{
	//char	a[] = "";

	printf("substr:%s\n", ft_substr("", 1, 1));
}*/
