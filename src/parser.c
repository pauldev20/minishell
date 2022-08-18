/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/18 11:10:36 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_cmds(char *input)
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

char	**parse_cmds(char *input)
{
	char	**arr;
	int		i;
	
	arr = ft_split(input, ' ');
	i = get_cmds(input);
	printf("%d\n", i);
	return (arr);
}

void	parse_input(char *input)
{
	char	**array;

	g_minishell.cmd_array = parse_cmds(input);
	array = g_minishell.cmd_array;
	while (*array)
	{
		builtin_parser(array);
		if (*array)
			array++;
	}
}
