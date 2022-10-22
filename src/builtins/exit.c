/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:30:59 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/22 22:26:15 by pgeeser          ###   ########.fr       */
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

int	builtin_exit(char *exit_code)
{
	if (is_number(exit_code))
		exit(ft_atoi(exit_code));
	ft_putstr_fd("numeric argument required\n", 2);
	exit(255);
}
