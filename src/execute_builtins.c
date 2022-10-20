/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:55:03 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/20 10:09:31 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**environ;

bool	is_own_builtin(char *cmd)
{
	if (cmd == NULL)
		return (false);
	else if (ft_strnstr(cmd, "cd", 2))
		return (true);
	else if (ft_strnstr(cmd, "echo", 4))
		return (true);
	else if (ft_strnstr(cmd, "pwd", 3))
		return (true);
	else if (ft_strnstr(cmd, "export", 7))
		return (true);
	else if (ft_strnstr(cmd, "unset", 6))
		return (true);
	else if (ft_strnstr(cmd, "env", 3))
		return (true);
	else if (ft_strnstr(cmd, "exit", 4))
		return (true);
	return (false);
}

int	execute_own_builtin(char *cmd, char *args)
{
	int		i;
	int		pipe_amount;
	char	**cmd_args;

	cmd = ft_strjoin(cmd, " ");
	cmd_args = ft_split(ft_strjoin(cmd, args), ' ');
	pipe_amount = get_pipe_amount(get_token_array(cmd_args));
	i = 0;
	while (cmd_args[i] != NULL)
		i++;
	return (builtin_parser(cmd_args, i, pipe_amount));
}
