/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:55:03 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/05 13:23:28 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

bool	is_own_builtin(char **cmd, int start_stop[2])
{
	if (cmd[start_stop[0]] == NULL)
		return (false);
	else if (ft_strnstr(cmd[start_stop[0]], "cd", 2))
		return (true);
	else if (ft_strnstr(cmd[start_stop[0]], "echo", 4))
		return (true);
	else if (ft_strnstr(cmd[start_stop[0]], "pwd", 3))
		return (true);
	else if (ft_strnstr(cmd[start_stop[0]], "export", 7))
		return (true);
	else if (ft_strnstr(cmd[start_stop[0]], "unset", 6))
		return (true);
	else if (ft_strnstr(cmd[start_stop[0]], "env", 3))
		return (true);
	else if (ft_strnstr(cmd[start_stop[0]], "exit", 4))
		return (true);
	return (false);
}

void	execute_own_builtin(char **cmd, int start_stop[2])
{
	char	*path;
	int		i;
	
	cmd = cut_start_stop(cmd, start_stop);
	i = 0;
	while (cmd[i] != NULL)
		i++;
	builtin_parser(cmd, i);
}