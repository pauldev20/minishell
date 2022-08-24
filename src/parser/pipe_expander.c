/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:37:57 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/24 19:37:15 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(const char *str, char *del)
{
	int	i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	while (*str)
	{
		i[0] += (!ft_strchr(del, *str) && !i[1] && !i[2] && !i[3]);
		i[1] = !ft_strchr(del, *str);
		i[2] += (*str == '\"') * (!i[2] + -(i[2]));
		i[3] += (*str == '\'') * (!i[3] + -(i[3]));
		str++;
	}
	if (i[2] || i[3])
		return (-1);
	return (i[0]);
}

static void	*free_arr(char **arr, int arr_count)
{
	while (arr_count >= 0)
		free(arr[arr_count--]);
	free(arr);
	return (NULL);
}

static char	**fill_array(char *s, int words, char *del, char **arr)
{
	int		i[4];
	char	*word_start;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	word_start = NULL;
	while (i[3] <= ft_strlen(s))
	{
		if (!ft_strchr(del, s[i[3]]) && !word_start && !i[1] && !i[2])
			word_start = s + i[3];
		else if ((ft_strchr(del, s[i[3]]) || s[i[3]] == '\0') && !i[1] && !i[2])
		{
			arr[i[0]] = ft_substr(word_start, 0, (s + i[3]) - word_start);
			if (!arr[i[0]++])
				return (free_arr(arr, i[0] - 1));
			word_start = NULL;
		}
		i[1] += (s[i[3]] == '\"') * (!i[1] + -(i[1]));
		i[2] += (s[i[3]++] == '\'') * (!i[2] + -(i[2]));
	}
	if (i[1] || i[2])
		return (free_arr(arr, i[0] - 1));
	return (arr);
}

static char	**set_split(char const *s, char *c)
{
	int		words;
	char	**arr;
	int		i;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	if (words < 0)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	arr[words] = NULL;
	if (!fill_array((char *)s, words, c, arr))
		return (NULL);
	return (arr);
}

void	**pipe_expander(char ***arr)
{
	int		i;
	int		j;
	int		g;
	int		v;
	char	**insert;
	char	**outarr;

	i = 0;
	g = 0;
	while ((*arr)[i])
	{
		insert = set_split((*arr)[i], "<|>");
		while ((*arr)[g])
			g++;
		j = 0;
		while (insert[j++])
			g++;
		outarr = (char **)malloc(sizeof(char *) * g);
		outarr[g] = NULL;
		j = 0;
		v = 0;
		while ((*arr)[j++] && j < i)
			outarr[v++] = (*arr)[j - 1];
		g = 0;
		while (insert[g])
			outarr[v++] = insert[g++];
		while ((*arr)[j])
			outarr[v++] = (*arr)[j++];
		printf("OUTARR: ");
		g = 0;
		while (outarr[g])
			printf("%s, ", outarr[g++]);
		printf("NULL\n");
		j = 0;
		while (insert[j++])
			i++;
		printf("NEXT i: %d\n", i);
		free(insert);
		(*arr) = outarr;
	}
	return (NULL);
}
