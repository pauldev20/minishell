/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:29:48 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/17 20:57:44 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_parser(char **array)
{
	while (*array)
	{
		if (ft_strncmp(*array, "echo", 5))
			builtin_echo(*array, array);
		array++;
	}
}

void	builtin_env(char **envp)
{
	int	c;

	c = 0;
	while (envp[c] != NULL)
	{
		printf("%s\n", envp[c]);
		c++;
	}
}