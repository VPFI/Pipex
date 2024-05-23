/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:16:12 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/23 17:01:17 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	check_character(int fd, char c, va_list pargs, int *printres)
{
	if (c == 'c')
		print_char(va_arg(pargs, int), printres, fd);
	else if (c == 's')
		print_string(va_arg(pargs, char *), printres, fd);
	else if (c == 'p')
	{
		prot_write("0x", 2, printres, fd);
		print_ptr(va_arg(pargs, unsigned long), printres, fd);
	}
	else if (c == 'i' || c == 'd')
		print_int(va_arg(pargs, int), printres, fd);
	else if (c == 'u')
		print_uns_int(va_arg(pargs, unsigned int), printres, fd);
	else if (c == 'x')
		print_hexa(va_arg(pargs, unsigned int), printres, 0, fd);
	else if (c == 'X')
		print_hexa(va_arg(pargs, unsigned int), printres, 1, fd);
	else if (c == '%')
		prot_write("%", 1, printres, fd);
	else
		print_char(c, printres, fd);
}

void	prot_write(char const *c, int len, int *printres, int fd)
{
	if (*printres == -1)
		return ;
	else if (write(fd, c, len) < 0)
		*printres = -1;
	else
		*printres += len;
}

int	ft_printf(int fd, char const *str, ...)
{
	int		i;
	int		printres;
	va_list	pargs;

	i = 0;
	printres = 0;
	va_start(pargs, str);
	while (str[i] && printres >= 0)
	{
		if (str[i] == '%')
		{
			i++;
			check_character(fd, str[i], pargs, &printres);
			i++;
		}
		if (str[i] != '%' && str[i] != '\0')
		{
			prot_write(&str[i], 1, &printres, fd);
			i++;
		}
	}
	va_end(pargs);
	return (printres);
}
/*
int	main(void)
{
	char	c = 'A';
	char	s[] = "hola q";
	int		i = -1231141;
	int		x = -45245;

}*/
