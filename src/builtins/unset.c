/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:24:21 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/18 10:40:32 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(char *key)
{
	int		i;
	t_env	*env;

	if (!key)
		return ;
	i = 0;
	env = g_minishell.envp;
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			remove_at_index(&g_minishell.envp, i);
		env = env->next;
		i++;
	}
}
