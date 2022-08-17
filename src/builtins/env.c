/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:29:48 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/17 22:34:25 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(void)
{
	int		i;
	char	**envp;

	i = 0;
	envp = g_minishell.envp;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i++]);
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
