/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:46:49 by vperez-f          #+#    #+#             */
/*   Updated: 2024/01/26 22:22:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destm;
	unsigned char	*srcm;
	size_t			i;

	destm = (unsigned char *)dest;
	srcm = (unsigned char *)src;
	i = 0;
	if (!n || srcm == destm)
		return (destm);
	while (i < n)
	{
		destm[i] = srcm[i];
		i++;
	}
	return (destm);
}
