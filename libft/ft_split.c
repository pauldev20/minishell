/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 22:33:42 by pgeeser           #+#    #+#             */
/*   Updated: 2022/04/07 19:51:25 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char del)
{
	int	count;
	int	current_word;

	count = 0;
	current_word = 0;
	while (*str)
	{
		if (*str != del && current_word == 0)
		{
			count++;
			current_word = 1;
		}
		else if (*str == del)
			current_word = 0;
		str++;
	}
	return (count);
}

static void	*free_arr(char **arr, int arr_count)
{
	while (arr_count >= 0)
		free(arr[arr_count--]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**arr;
	int			arr_i;
	char const	*word_start;
	int			words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	arr_i = 0;
	while (arr_i < words)
	{
		while (*s == c)
			s++;
		word_start = s;
		while (*s != c && *s)
			s++;
		arr[arr_i++] = ft_substr(word_start, 0, s - word_start);
		if (!arr[arr_i - 1])
			return (free_arr(arr, arr_i - 1));
	}
	arr[arr_i] = NULL;
	return (arr);
}
