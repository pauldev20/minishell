/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:54:57 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/20 15:21:33 by pgeeser          ###   ########.fr       */
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
	int		i;
	int		j;
	t_env	*env;
	t_env	*newenv;

	i = 0;
	env = g_minishell.envp;
	if (argc < 1)
	{
		builtin_env();
		return (1);
	}
	while (env)
	{
		env = env->next;
		i++;
	}
	j = 0;
	while (argv[j])
	{
		newenv = create_new(argv[j++]);
		env = g_minishell.envp;
		if (newenv)
		{
			printf("NEWENV: %s\n", newenv->key);
			while (env)
			{
				if (ft_strncmp(env->key, newenv->key, ft_strlen(env->key)) == 0)
				{
					printf("Allready in ENV!! %s\n", env->key);
					free(newenv->key);
					free(env->value);
					env->value = newenv->value;
					free(newenv);
					break ;
				}
				env = env->next;
			}
			if (env == NULL)
			{
				printf("Not in ENV!\n");
				add_at_index(&g_minishell.envp, newenv, i++);
			}
		}
	}
	return (1);
}
