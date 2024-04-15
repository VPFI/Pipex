/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 19:39:46 by vperez-f          #+#    #+#             */
/*   Updated: 2024/01/26 22:22:22 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*temp_dest;
	unsigned char	*temp_src;
	int				len;

	temp_dest = (unsigned char *)dest;
	temp_src = (unsigned char *)src;
	len = n - 1;
	if (src < dest)
	{
		while (0 <= len)
		{
			temp_dest[len] = temp_src[len];
			len--;
		}
	}
	else if (dest <= src)
	{
		ft_memcpy(dest, src, n);
	}
	return (dest);
}
