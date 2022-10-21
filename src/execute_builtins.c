/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 10:55:03 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/21 18:06:29 by mhedtman         ###   ########.fr       */
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

int	execute_own_builtin(char *cmd, char **args)
{
	int		i;
	char	**cmd_args;

	cmd_args = get_cmd_arg_arr(cmd, args);
	i = 0;
	while (cmd_args[i] != NULL)
		i++;
	return (builtin_parser(cmd_args, i));
}

bool	is_last_cmd(char **cmd_arr)
{
	int	i;

	i = 0;
	while (cmd_arr[i] != NULL)
	{
		if (str_is_equal(cmd_arr[i], "|"))
			return (false);
		i++;
	}
	return (true);
}

char	**catch_builtins(char **cmds, int *i, int *offset)
{
	int	j;

	while (cmds[*i] != NULL)
	{
		if (str_is_equal(cmds[*i], "unset") || str_is_equal(cmds[*i], "export")
			|| str_is_equal(cmds[*i], "cd"))
		{
			if (is_last_cmd(cmds + (*i)))
			{
				j = 0;
				while (cmds[j] != NULL)
					j++;
				builtin_parser(cmds + (*i), j);
				free_array(cmds);
				return (empty_arr());
			}
			*offset += 2;
			if (cmds[*i + *offset] != NULL && cmds[*i + *offset][0] == '|')
				*offset += 1;
		}
		cmds[*i] = cmds[*i + *offset];
		*i += 1;
	}
	return (cmds);
}
