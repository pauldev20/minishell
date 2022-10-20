/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:11:18 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/20 01:07:44 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipe_error(char *str)
{
	while (*str)
	{
		if (ft_strncmp(str, "< <", 3) == 0)
			return (1);
		if (ft_strncmp(str, "> >", 3) == 0)
			return (1);
		str++;
	}
	return (0);
}

static int	count_words(const char *str, char del)
{
	int	i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	while (*str)
	{
		i[0] += (*str != del && !i[1] && !i[2] && !i[3]);
		i[1] = (*str != del);
		i[2] += (*str == '\"') * (!i[2] + -(i[2]));
		i[3] += (*str == '\'') * (!i[3] + -(i[3]));
		str++;
	}
	if (i[2] || i[3])
		return (-1);
	return (i[0]);
}

void	*free_arr(char **arr, int arr_count)
{
	while (arr_count >= 0)
		free(arr[arr_count--]);
	free(arr);
	return (NULL);
}

static char	**fill_array(char *s, char del, char **arr)
{
	int		i[4];
	char	*word_start;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	word_start = NULL;
	while (i[3] <= (int)ft_strlen(s))
	{
		if (s[i[3]] != del && !word_start && !i[1] && !i[2])
			word_start = s + i[3];
		else if ((s[i[3]] == del || s[i[3]] == '\0') && !i[1] && !i[2])
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

char	**lexer(char const *s, char c)
{
	int		words;
	char	**arr;

	if (!s)
		return (NULL);
	if (check_pipe_error((char *)s))
		return (NULL);
	words = count_words(s, c);
	if (words < 0)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	arr[words] = NULL;
	if (!fill_array((char *)s, c, arr))
		return (NULL);
	return (arr);
}
