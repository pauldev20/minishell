/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_prejobs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:04:54 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/13 12:08:55 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	JOINS '>' + '>' AND '<' + '<' IF NEEDED */
char	**join_io_modifier(char **arr)
{
	int	old_i;
	int	new_i;

	old_i = 0;
	new_i = 0;
	while (arr[old_i] != NULL)
	{
		if (arr[old_i + 1] != NULL)
		{
			if (arr[old_i][0] == '<' && arr[old_i + 1][0] == '<')
			{
				arr[new_i] = ft_strjoin(arr[old_i], "<");
				old_i++;
			}
			else if (arr[old_i][0] == '>' && arr[old_i + 1][0] == '>')
			{
				arr[new_i] = ft_strjoin(arr[old_i], ">");
				old_i++;
			}
			else
				arr[new_i] = arr[old_i];
		}
		else
			arr[new_i] = arr[old_i];
		new_i++;
		old_i++;
	}
	while (new_i < old_i)
	{
		arr[new_i] = NULL;
		new_i++;
	}
	arr[new_i] = NULL;
	return (arr);
}

/* CHECKS FOR GRAMMAR MISTAKES IN THE SYNTAX*/
bool	check_syntax(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strnstr(tokens[i], "PIPE", 4))
		{
			if (tokens[i - 1] == NULL || tokens[i + 1] == NULL
				|| ft_strnstr(tokens[i - 1], "PIPE", 4)
				|| ft_strnstr(tokens[i + 1], "PIPE", 4))
			{
				printf("\033[31mminishell: syntax error near pipe\n");
				return (false);
			}
		}
		else if (is_input_redirector(tokens[i])
			|| is_output_redirector(tokens[i]))
		{
			if (tokens[i + 1] == NULL || is_input_redirector(tokens[i + 1]) || is_input_redirector(tokens[i + 1]))
			{
				printf("\033[31mminishell: syntax error near io-modifier\n");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

char	**execute_prejobs(char **arr)
{
	char	**token_array;

	arr = join_io_modifier(arr);
	token_array = get_token_array(arr);
	if (!check_syntax(token_array))
		return (NULL);
	return (arr);
}
