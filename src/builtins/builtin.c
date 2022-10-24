/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:29:48 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/24 11:01:34 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*delete_caps(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] -= 32;
		i++;
	}
	return (str);
}

int	builtin_parser(char **argv, int argc)
{
	*argv = delete_caps(*argv);
	if (ft_strncmp(*argv, "echo", 5) == 0)
		exit (builtin_echo(argv + 1, argc - 1));
	if (ft_strncmp(*argv, "exit", 5) == 0)
		exit (builtin_exit(argv[1], argv + 1));
	if (ft_strncmp(*argv, "env", 4) == 0)
		exit (builtin_env());
	if (ft_strncmp(*argv, "cd", 2) == 0)
		return (builtin_cd(argv[1]));
	if (ft_strncmp(*argv, "export", 7) == 0)
		return (builtin_export(argv + 1, argc - 1));
	if (ft_strncmp(*argv, "unset", 6) == 0)
		return (builtin_unset(argv + 1, argc - 1));
	if (ft_strncmp(*argv, "pwd\0", 4) == 0)
		exit (builtin_pwd());
	exit (255);
}
