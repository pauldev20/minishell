/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:54:57 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/20 20:41:41 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_new(char *str)
{
	t_env	*new;
	char	**array;

	if (!ft_strrchr(str, '='))
		return (NULL);
	array = ft_split(str, '=');
	if (!array[0])
	{
		free_array(array);
		return (NULL);
	}
	new = (t_env *)malloc(sizeof(t_env));
	new->next = NULL;
	new->key = array[0];
	if (array[1])
		new->value = array[1];
	else
		new->value = (char *)ft_calloc(1, sizeof(char));
	free(array);
	return (new);
}

int	builtin_export(char	**argv, int argc)
{
	int		i[2];
	t_env	*env;
	t_env	*newenv;

	if (argc < 1)
		return (builtin_env());
	i[1] = 0;
	while (argv[i[1]])
	{
		i[0] = 0;
		env = g_minishell.envp;
		newenv = create_new(argv[i[1]++]);
		while (newenv && env)
		{
			if (ft_strncmp(env->key, newenv->key, ft_strlen(env->key)) == 0)
			{
				free(newenv->key);
				free(env->value);
				env->value = newenv->value;
				free(newenv);
				break ;
			}
			env = env->next;
			i[0]++;
		}
		if (newenv && !env)
			add_at_index(&g_minishell.envp, newenv, i[0]);
	}
	return (EXIT_SUCCESS);
}
