/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:24:21 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/19 12:02:13 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(char **argv, int argc)
{
	int		i;
	int		j;
	t_env	*env;

	if (argc < 1)
		return ;
	j = 0;
	while (argv[j])
	{
		i = 0;
		env = g_minishell.envp;
		while (env)
		{
			if (ft_strncmp(env->key, argv[j], ft_strlen(argv[j]) + 1) == 0)
				remove_at_index(&(g_minishell.envp), i);
			env = env->next;
			i++;
		}
		j++;
	}
}
