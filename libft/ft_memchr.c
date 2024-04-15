/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:10:04 by vperez-f          #+#    #+#             */
/*   Updated: 2024/01/29 19:27:03 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*temps;

	temps = (char *)s;
	while (0 < n)
	{
		if (*temps == (char) c)
		{
			return (temps);
		}
		n--;
		temps++;
	}
	return (NULL);
}
