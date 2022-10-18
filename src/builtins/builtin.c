/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:29:48 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/18 11:49:07 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_parser(char **argv, int argc, int pipe_amount)
{
	int	fail;

	if (ft_strncmp(*argv, "echo", 5) == 0)
		exit (builtin_echo(argv + 1, argc - 1));
	if (ft_strncmp(*argv, "exit", 5) == 0)
		exit (builtin_exit(argv[1]));
	if (ft_strncmp(*argv, "env", 4) == 0)
		builtin_env();
	if (ft_strncmp(*argv, "export", 7) == 0)
		return (builtin_export(argv + 1, argc - 1));
	if (ft_strncmp(*argv, "unset", 6) == 0)
		return (builtin_unset(argv + 1, argc - 1));
	if (ft_strncmp(*argv, "pwd\0", 4) == 0)
		exit (builtin_pwd());
	if (ft_strncmp(*argv, "cd", 2) == 0)
		return (builtin_cd(argv[1], pipe_amount));
	exit (255);
}
