/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:29:48 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/19 10:46:00 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_parser(char **argv, int argc)
{
	if (ft_strncmp(*argv, "echo", 5) == 0)
		builtin_echo(argv + 1, argc - 1);
	if (ft_strncmp(*argv, "exit", 5) == 0)
		builtin_exit();
	if (ft_strncmp(*argv, "env", 4) == 0)
		builtin_env();
	if (ft_strncmp(*argv, "export", 7) == 0)
		builtin_export(argv + 1, argc - 1);
	if (ft_strncmp(*argv, "unset", 6) == 0)
		builtin_unset(argv + 1, argc - 1);
	// while (*argv)
	// {
	// 	// if (ft_strncmp(*array, "unset\0", 6) == 0)
	// 	// 	builtin_unset(*(array + 1));
	// 	// if (ft_strncmp(*array, "pwd\0", 4) == 0)
	// 	// 	builtin_pwd();
	// 	argv++;
	// }
}
