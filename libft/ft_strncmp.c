/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:24:13 by vperez-f          #+#    #+#             */
/*   Updated: 2024/01/29 19:40:31 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ts1;
	unsigned char	*ts2;

	i = 0;
	ts1 = (unsigned char *)s1;
	ts2 = (unsigned char *)s2;
	if (n == 0)
	{
		return (0);
	}
	while ((ts1[i] != '\0') && (ts2[i] != '\0') && (i < n - 1))
	{
		if (ts1[i] != ts2[i])
		{
			return (ts1[i] - ts2[i]);
		}
		i++;
	}
	return (ts1[i] - ts2[i]);
}
