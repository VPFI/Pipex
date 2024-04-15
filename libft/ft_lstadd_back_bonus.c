/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:06:51 by vperez-f          #+#    #+#             */
/*   Updated: 2024/01/24 20:45:59 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_entry;

	if (lst)
	{
		if (*lst)
		{
			last_entry = ft_lstlast(*lst);
			last_entry->next = new;
		}
		else
			*lst = new;
	}
}
