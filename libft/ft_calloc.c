/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:49:37 by vperez-f          #+#    #+#             */
/*   Updated: 2024/01/16 18:10:08 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	char	*temp;
	size_t	i;

	i = 0;
	ptr = (void *)malloc(nmemb * size);
	temp = (char *)ptr;
	if (!ptr)
		return (NULL);
	while (i < (nmemb * size))
	{
		temp[i] = 0;
		i++;
	}
	return (ptr);
}
