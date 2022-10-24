/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:30:59 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/24 10:07:58 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_number(char *string)
{
	int	i;

	i = 0;
	if (string[0] == '+' || string[0] == '-')
	{
		i++;
		if (string[i] == '\0')
			return (false);
	}
	while (string[i] != '\0')
	{
		if (string[i] < '0' || string[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	get_argc_exit(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	return (i);
}

int	builtin_exit(char *exit_code, char **argv)
{
	int	argc;

	argc = 0;
	if (argv != NULL)
		argc = get_argc_exit(argv);
	if (argc > 1)
	{
		ft_putstr_fd("too many arguments\n", 2);
		exit (1);
	}
	if (is_number(exit_code))
		exit(ft_atoi(exit_code));
	ft_putstr_fd("numeric argument required\n", 2);
	exit(255);
}
