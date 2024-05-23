/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:46:48 by vperez-f          #+#    #+#             */
/*   Updated: 2024/05/23 17:19:21 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>

int		ft_printf(int fd, char const *str, ...);

void	print_char(int c, int *printres, int fd);
void	print_string(char *s, int *printres, int fd);
void	print_ptr(unsigned long ptr, int *printres, int fd);
void	print_int(int num, int *printres, int fd);
void	print_uns_int(unsigned int num, int *printres, int fd);
void	print_hexa(unsigned int num, int *printres, int caps, int fd);
void	prot_write(char const *c, int len, int *printres, int fd);

#endif
