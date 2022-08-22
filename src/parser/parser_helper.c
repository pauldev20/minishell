/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:02:14 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/20 14:53:22 by mhedtman         ###   ########.fr       */
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
