/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:29:48 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/18 11:19:03 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_parser(char **array)
{
	while (*array)
	{
		if (ft_strncmp(*array, "echo\0", 5) == 0)
		{
			if (*(array + 1) && ft_strncmp(*(array + 1), "-n\0", 3) == 0)
				builtin_echo(array + 2, 0);
			else
				builtin_echo(array + 1, 1);
		}
		if (ft_strncmp(*array, "exit\0", 5) == 0)
			builtin_exit();
		if (ft_strncmp(*array, "env\0", 4) == 0)
			builtin_env();
		if (ft_strncmp(*array, "export\0", 7) == 0)
			builtin_export(array + 1);
		if (ft_strncmp(*array, "unset\0", 6) == 0)
			builtin_unset(*(array + 1));
		if (ft_strncmp(*array, "pwd\0", 4) == 0)
			builtin_pwd();
		array++;
	}
}
