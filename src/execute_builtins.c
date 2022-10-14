/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:55:03 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/14 13:17:53 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

bool	is_own_builtin(char **cmd)
{
	if (cmd[0] == NULL)
		return (false);
	else if (ft_strnstr(cmd[0], "cd", 2))
		return (true);
	else if (ft_strnstr(cmd[0], "echo", 4))
		return (true);
	else if (ft_strnstr(cmd[0], "pwd", 3))
		return (true);
	else if (ft_strnstr(cmd[0], "export", 7))
		return (true);
	else if (ft_strnstr(cmd[0], "unset", 6))
		return (true);
	else if (ft_strnstr(cmd[0], "env", 3))
		return (true);
	else if (ft_strnstr(cmd[0], "exit", 4))
		return (true);
	return (false);
}

int	execute_own_builtin(char **cmd)
{
	char	*path;
	int		i;
	int		pipe_amount;

	pipe_amount = get_pipe_amount(get_token_array(cmd));
	i = 0;
	while (cmd[i] != NULL)
		i++;
	return (builtin_parser(cmd, i, pipe_amount));
}
