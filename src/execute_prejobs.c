/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_prejobs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:04:54 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/24 16:37:44 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	JOINS '>' + '>' AND '<' + '<' IF NEEDED */
char	**join_io_modifier(char **arr)
{
	int		old_i;
	int		new_i;
	char	**new_arr;

	old_i = 0;
	new_i = 0;
	new_arr = (char **)ft_calloc(array_len(arr) + 1, sizeof(char *));
	while (arr[old_i] != NULL)
	{
		if (arr[old_i + 1] != NULL)
			new_arr[new_i] = join_ios(arr, &old_i);
		else
			new_arr[new_i] = ft_strdup(arr[old_i]);
		new_i++;
		old_i++;
	}
	free_array(arr);
	return (new_arr);
}

bool	check_pre_syntax(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (is_input_redirector(tokens[i])
			|| is_output_redirector(tokens[i]))
		{
			if (!syntax_io_error(tokens, i))
				return (false);
		}
		i++;
	}
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

	token_array = get_token_array(arr);
	if (!check_syntax(token_array))
	{
		free_array(token_array);
		return (NULL);
	}
	free_array(token_array);
	return (arr);
}
