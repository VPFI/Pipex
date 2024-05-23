/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:49:05 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/23 16:58:54 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hexa(unsigned int num, int *printres, int caps, int fd)
{
	unsigned int	nb;
	int				base;
	char			*hexa_base[2];

	hexa_base[0] = "0123456789abcdef";
	hexa_base[1] = "0123456789ABCDEF";
	base = 16;
	nb = num;
	if (0 <= nb && nb <= 15)
		prot_write(&hexa_base[caps][(nb % base)], 1, printres, fd);
	else
	{
		print_hexa(nb / base, printres, caps, fd);
		print_hexa(nb % base, printres, caps, fd);
	}
}
