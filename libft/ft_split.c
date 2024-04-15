/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vperez-f <vperez-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:13:55 by vperez-f          #+#    #+#             */
/*   Updated: 2024/01/26 21:56:54 by vperez-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char sep)
{
	int	i;
	int	word_flag;
	int	word_count;

	i = 0;
	word_flag = 0;
	word_count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != sep && word_flag == 0)
		{
			word_count++;
			word_flag = 1;
		}
		else if (s[i] == sep)
			word_flag = 0;
		i++;
	}
	return (word_count);
}

static char	*to_array_words(char const **s, char sep)
{
	int		i;
	int		start_count;
	char	*w_res;

	i = 0;
	start_count = 0;
	while (**s == sep)
		*s = *s + 1;
	while (*(*s + i) != sep && *(*s + i) != '\0')
		i++;
	w_res = ft_substr(*s, start_count, (i - start_count));
	*s = *s + i;
	return (w_res);
}

static void	free_all(char **res, int i)
{
	while (0 <= i)
	{
		free(res[i]);
		i--;
	}
	free(res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		w_count;
	char	**res;

	i = 0;
	w_count = word_count(s, c);
	res = (char **)malloc(sizeof(char *) * (w_count + 1));
	if (!res)
		return (NULL);
	while (i < w_count)
	{
		res[i] = to_array_words(&s, c);
		if (!res[i])
		{
			free_all(res, i);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}
/*
int	main(void)
{
	int		i = 0;
	char	**res = ft_split("", 'z');

	while (res[i] != NULL)
	{
		printf("s%i:%s\n", i, res[i]);
		i++;
	}
	return (0);
}*/