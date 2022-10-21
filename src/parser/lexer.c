/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:11:18 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/21 14:17:31 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe_error(char *str)
{
	int	i[2];

	i[0] = 0;
	i[1] = 0;
	while (*str)
	{
		i[0] += (*str == '\"') * (!i[0] + -(i[0]));
		i[1] += (*str == '\'') * (!i[1] + -(i[1]));
		if (ft_strncmp(str, "< <", 3) == 0 && !i[0] && !i[1])
			return (2);
		if (ft_strncmp(str, "> >", 3) == 0 && !i[0] && !i[1])
			return (2);
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

static char	**fill_array(char *s, char del, char **arr)
{
	int		i[4];
	char	*w_st;

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	w_st = NULL;
	while (i[3] <= (int)ft_strlen(s))
	{
		if (s[i[3]] != del && !w_st && !i[1] && !i[2])
			w_st = s + i[3];
		else if ((s[i[3]] == del || s[i[3]] == '\0') && !i[1] && !i[2] && w_st)
		{
			arr[i[0]] = ft_substr(w_st, 0, (s + i[3]) - w_st);
			if (!arr[i[0]++])
				return (free_arr(arr, i[0] - 1));
			w_st = NULL;
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
	{
		print_error(SYNTAX_PIPE, "", -131);
		return (NULL);
	}
	words = count_words(s, c);
	if (words < 0)
		return (NULL);
	arr = (char **)ft_calloc((words + 1), sizeof(char *));
	if (!fill_array((char *)s, c, arr))
		return (NULL);
	return (arr);
}
