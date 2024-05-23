/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:49:10 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/23 16:59:28 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_int(int num, int *printres, int fd)
{
	int		nb;
	int		base;
	char	*hexa_base;

	hexa_base = "0123456789abcdef";
	base = 10;
	nb = num;
	if (nb == -2147483648)
	{
		prot_write("-2", 2, printres, fd);
		nb = 147483648;
	}
	if (nb < 0)
	{
		prot_write("-", 1, printres, fd);
		nb = nb * (-1);
	}
	if (0 <= nb && nb <= 9)
		prot_write(&hexa_base[(nb % base)], 1, printres, fd);
	else
	{
		print_int(nb / base, printres, fd);
		print_int(nb % base, printres, fd);
	}
}

void	print_uns_int(unsigned int num, int *printres, int fd)
{
	unsigned int	nb;
	int				base;
	char			*hexa_base;

	hexa_base = "0123456789abcdef";
	base = 10;
	nb = num;
	if (0 <= nb && nb <= 9)
		prot_write(&hexa_base[(nb % base)], 1, printres, fd);
	else
	{
		print_uns_int(nb / base, printres, fd);
		print_uns_int(nb % base, printres, fd);
	}
}
