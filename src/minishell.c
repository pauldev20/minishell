/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:07:25 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/17 20:22:31 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(void)
{
	extern char	**environ;
	char		*input;
	char		**envp;

	while (1)
	{
		input = readline("➜  minishell: ");
		add_history(input);
		envp = arr_dup(environ);
		for (int c = 0; envp[c] != NULL; c ++)
			printf("%s\n", envp[c]);
	}
	free (input);
}
