/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/19 09:45:34 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_arr_words(char *input)
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
	int c;

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
	int c;
	
	c = 0;
	while ((*source != '\'' && *source != '\"') && *source != '\0')
	{
		c ++;
		source++;
	}
	// c++;
	return (c);
}
char	**parse_cmds(char *input, int *argc)
{
	char	**arr;
	char	*word_start;
	int		arr_start;
	int		len;
	bool	quotes;
	
	*argc = get_arr_words(input);
	arr = (char **)malloc(sizeof(char *) * (*argc + 1));
	arr[*argc] = NULL;
	arr_start = 0;
	while (arr_start < *argc)
	{
		quotes = false;
		while (*input == ' ')
			input++;
		word_start = input;
		if (*word_start == '\"' || *word_start == '\'')
		{
			quotes = true;
			word_start ++;
		}
		len = 0;
		if (quotes == true)
			len = get_len_quotes(word_start);
		else
			len = get_len_normal(word_start);
		arr[arr_start++] = ft_substr(word_start, 0, len);
		if (quotes == true)
			len++;
		input = word_start + len;
	}
	return (arr);
}

void	parse_input(char *input)
{
	char	**array;
	int		argc;
	
	g_minishell.cmd_array = parse_cmds(input, &argc);
	printf("ARGC: %d\n", argc);
	array = g_minishell.cmd_array;
	for(int i = 0; array[i] != NULL; i++)
		printf("ARGV: %s\n", array[i]);
	while (*array)
	{
		builtin_parser(array);
		if (*array)
			array++;
	}
}
