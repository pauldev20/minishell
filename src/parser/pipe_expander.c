/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 18:37:57 by pgeeser           #+#    #+#             */
/*   Updated: 2022/09/27 10:13:05 by mhedtman         ###   ########.fr       */
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
	while (str && *str)
	{
		if ((ft_strchr(del, *str) && !i[2] && !i[3])
			|| (!ft_strchr(del, *str) && !i[1] && !i[2] && !i[3]))
			i[0]++;
		i[1] = !ft_strchr(del, *str);
		i[2] += (*str == '\"') * (!i[2] + -(i[2]));
		i[3] += (*str++ == '\'') * (!i[3] + -(i[3]));
	}
	if (i[2] || i[3])
		return (-1);
	return (i[0]);
}

static char	**fill_array(char *s, char *del, char **arr)
{
	int		i[5];

	i[0] = 0;
	i[1] = 0;
	i[3] = 0;
	i[4] = 0;
	while (s && s[i[0]])
	{
		i[2] = i[0];
		if (ft_strchr(del, s[i[0]]))
			arr[i[1]++] = ft_substr(s, i[2], (i[0]++ + 1) - i[2]);
		else
		{
			while (s[i[0]] && (!ft_strchr(del, s[i[0]]) || i[3] || i[4]))
			{
				i[3] += (s[i[0]] == '\"') * (!i[3] + -(i[3]));
				i[4] += (s[i[0]++] == '\'') * (!i[4] + -(i[4]));
			}
			arr[i[1]++] = ft_substr(s, i[2], i[0] - i[2]);
		}
	}
	if (i[3] || i[4])
		return (free_arr(arr, i[1] - 1));
	return (arr);
}

static char	**set_split(char const *s, char *c)
{
	int		words;
	char	**arr;

	if (!s)
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

int	insert_into_arr(char ***arr, char **insert, int index)
{
	int		i[3];
	char	**outarr;

	i[0] = 0;
	while ((*arr)[i[0]])
		i[0]++;
	i[1] = 0;
	while (insert[i[1]])
		i[1]++;
	outarr = (char **)malloc(sizeof(char *) * (i[0] + i[1] + 1 - (i[1] > 0)));
	outarr[i[0] + i[1] - (i[1] > 0)] = NULL;
	i[1] = 0;
	i[0] = 0;
	while (i[0]++ < index)
		outarr[i[1]++] = (*arr)[i[0] - 1];
	free((*arr)[i[0] - 1]);
	i[2] = 0;
	while (insert[i[2]])
		outarr[i[1]++] = insert[i[2]++];
	while ((*arr)[i[0]])
		outarr[i[1]++] = (*arr)[i[0]++];
	free(*arr);
	(*arr) = outarr;
	return (i[2]);
}

void	**pipe_expander(char ***arr)
{
	int		i;
	int		g;
	char	**insert;

	i = 0;
	while ((*arr)[i])
	{
		insert = set_split((*arr)[i], "<|>");
		if (!insert)
			return (NULL);
		g = 0;
		insert_into_arr(arr, insert, i);
		free(insert);
		i++;
	}
	return (NULL);
}
