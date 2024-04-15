/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:18:49 by vperez-f          #+#    #+#             */
/*   Updated: 2024/01/16 19:05:38 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*temps1;
	unsigned char	*temps2;

	temps1 = (unsigned char *)s1;
	temps2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (0 < (n - 1))
	{
		if (*temps1 != *temps2)
			return (*temps1 - *temps2);
		temps1++;
		temps2++;
		n--;
	}
	return (*temps1 - *temps2);
}
/*
int	main (void)
{
	printf("ft: %i\n", ft_memcmp("abcde", "abcde", -15));
	printf("O:  %i\n", memcmp("abcde", "abcde", -15));
}*/
