/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:02:14 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/25 10:38:49 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

bool	is_delimiter(t_token i)
{
	if (i == DLESS || i == PIPE || i == DGREAT || i == LESS || i == GREAT)
		return (true);
	return (false);
}

int	get_arr_words(char *input)
{
	int	count;
	int	current_word;

	count = 0;
	current_word = 0;
	while (*input)
	{
		if (*input != ' ' && current_word == 0)
		{
			count++;
			current_word = 1;
		}
		if (*input == '\"' || *input == '\'')
		{
			input++;
			while (*input != '\"' || *input == '\'')
				input++;
		}
		else if (*input == ' ')
			current_word = 0;
		input++;
	}
	return (count);
}

int	get_len_normal(char *source)
{
	int	c;

	c = 0;
	while (*source != ' ' && *source != '\0')
	{
		c ++;
		source++;
	}
	return (c);
}

int	get_len_quotes(char *source)
{
	int	c;

	c = 0;
	while ((*source != '\'' && *source != '\"') && *source != '\0')
	{
		c ++;
		source++;
	}
	c++;
	return (c);
}

void	*free_arr(char **arr, int arr_count)
{
	while (arr_count >= 0)
		free(arr[arr_count--]);
	free(arr);
	return (NULL);
}
