/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_prejobs_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:13:14 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/22 16:20:55 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	syntax_io_error(char **tokens, int i)
{
	if (tokens[i + 1] == NULL || is_input_redirector(tokens[i + 1])
		|| is_output_redirector(tokens[i + 1]))
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

char	*join_ios(char **arr, int *old_i)
{
	if (arr[*old_i][0] == '<' && arr[*old_i + 1][0] == '<')
	{
		*old_i = *old_i + 1;
		return (ft_strdup("<<"));
	}
	else if (arr[*old_i][0] == '>' && arr[*old_i + 1][0] == '>')
	{
		*old_i = *old_i + 1;
		return (ft_strdup(">>"));
	}
	else if (arr[*old_i][0] == '<' && arr[*old_i + 1][0] == '>')
	{
		*old_i = *old_i + 1;
		return (ft_strdup("<>"));
	}
	else
		return (ft_strdup(arr[*old_i]));
}
