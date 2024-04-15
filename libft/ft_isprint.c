/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 20:27:41 by vperez-f          #+#    #+#             */
/*   Updated: 2024/01/15 15:08:39 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (32 <= c && c <= 126)
		return (1);
	return (0);
}
/*
int main (void)
{
	int	i;

	i = 0;
	while ((ft_isprint(i) == isprint(i)) && i < 200)
		i++;
	printf("c: %i", i);
	return(0);
}*/
