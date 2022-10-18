/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_prejobs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:04:54 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/18 14:24:44 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_ios(char **arr, int *old_i)
{
	if (arr[*old_i][0] == '<' && arr[*old_i + 1][0] == '<')
	{
		*old_i = *old_i + 1;
		return (ft_strjoin(arr[*old_i - 1], "<"));
	}
	else if (arr[*old_i][0] == '>' && arr[*old_i + 1][0] == '>')
	{
		*old_i = *old_i + 1;
		return (ft_strjoin(arr[*old_i - 1], ">"));
	}
	else if (arr[*old_i][0] == '<' && arr[*old_i + 1][0] == '>')
	{
		*old_i = *old_i + 1;
		return (ft_strjoin(arr[*old_i], ">"));
	}
	else
		return (arr[*old_i]);
}

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
			arr[new_i] = join_ios(arr, &old_i);
		else
			arr[new_i] = arr[old_i];
		new_i++;
		old_i++;
	}
	while (new_i <= old_i)
	{
		arr[new_i] = NULL;
		new_i++;
	}
	return (arr);
}

bool	syntax_io_error(char **tokens, int i)
{
	if (tokens[i + 1] == NULL || is_input_redirector(tokens[i + 1])
		|| is_input_redirector(tokens[i + 1]))
		return (false);
	return (true);
}

bool	syntax_pipe_error(char **tokens, int i)
{
	if (tokens[i - 1] == NULL || tokens[i + 1] == NULL
		|| ft_strnstr(tokens[i - 1], "PIPE", 4)
		|| ft_strnstr(tokens[i + 1], "PIPE", 4))
		return (false);
	return (true);
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
			if (!syntax_pipe_error(tokens, i))
				print_error(5, NULL, 2);
		}
		else if (is_input_redirector(tokens[i])
			|| is_output_redirector(tokens[i]))
		{
			if (!syntax_io_error(tokens, i))
				print_error(6, NULL, 2);
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
