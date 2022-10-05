/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:29:48 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/05 14:45:56 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_parser(char **argv, int argc, int pipe_amount)
{
	int	fail;

	fail = 1;
	if (ft_strncmp(*argv, "echo", 5) == 0)
		fail = builtin_echo(argv + 1, argc - 1);
	if (ft_strncmp(*argv, "exit", 5) == 0)
		builtin_exit();
	if (ft_strncmp(*argv, "env", 4) == 0)
		builtin_env();
	if (ft_strncmp(*argv, "export", 7) == 0)
		fail = builtin_export(argv + 1, argc - 1);
	if (ft_strncmp(*argv, "unset", 6) == 0)
		fail = builtin_unset(argv + 1, argc - 1);
	if (ft_strncmp(*argv, "pwd\0", 4) == 0)
		fail = builtin_pwd();
	if (ft_strncmp(*argv, "cd", 2) == 0)
		fail = builtin_cd(argv[1], pipe_amount);
	return (fail);
}
