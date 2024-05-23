/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:46:04 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/23 16:59:53 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(int c, int *printres, int fd)
{
	prot_write((char const *)&c, 1, printres, fd);
}

void	print_string(char *s, int *printres, int fd)
{
	int	i;

	i = 0;
	if (!s)
	{
		prot_write("(null)", 6, printres, fd);
		return ;
	}
	while (s[i] != '\0')
	{
		prot_write(&s[i], 1, printres, fd);
		i++;
	}
}
