/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:48:09 by vperez-f          #+#    #+#             */
/*   Updated: 2024/01/25 18:54:05 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	to_str(int nb, char *num, int *i)
{
	if (nb == -2147483648)
	{
		num[0] = '-';
		num[1] = '2';
		*i = 2;
		nb = 147483648;
	}
	else if (nb < 0)
	{
		num[0] = '-';
		nb = (-1) * nb;
		*i = *i + 1;
	}
	if (0 <= nb && nb <= 9)
	{
		num[*i] = nb + '0';
		*i = *i + 1;
	}
	else
	{
		to_str(nb / 10, num, i);
		to_str(nb % 10, num, i);
	}
}

static void	count_digits(int nb, int *count)
{
	if (nb == -2147483648)
	{
		*count = 2;
		nb = 147483648;
	}
	if (nb < 0)
	{
		*count = *count + 1;
		nb = nb * (-1);
	}
	if (0 < nb)
	{
		*count = *count + 1;
		count_digits(nb / 10, count);
	}
}

char	*ft_itoa(int n)
{
	char	*num;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (n == 0)
		return (ft_strdup("0"));
	count_digits(n, &count);
	num = (char *)malloc(((sizeof(char) * count + 1)));
	if (!num)
		return (NULL);
	to_str(n, num, &i);
	num[i] = '\0';
	return (num);
}
/*
// works with octal as well
int	main(void)
{
	printf("num: %s\n", ft_itoa(0));
}*/
