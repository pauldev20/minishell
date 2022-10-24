/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:54:57 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/24 10:28:19 by mhedtman         ###   ########.fr       */
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
	new = (t_env *)ft_calloc(1, sizeof(t_env));
	new->next = NULL;
	new->key = array[0];
	if (array[1])
		new->value = array[1];
	else
		new->value = (char *)ft_calloc(1, sizeof(char));
	free(array);
	return (new);
}

static int	replace_existing(t_env	**newenv, t_env	**env)
{
	int	i;

	i = 0;
	while (*newenv && *env)
	{
		if (ft_strncmp((*env)->key,
				(*newenv)->key, ft_strlen((*env)->key)) == 0)
		{
			free((*newenv)->key);
			free((*env)->value);
			(*env)->value = (*newenv)->value;
			free(*newenv);
			break ;
		}
		(*env) = (*env)->next;
		i++;
	}
	return (i);
}

int	builtin_export(char	**argv, int argc)
{
	int		i[2];
	t_env	*env;
	t_env	*newenv;

	if (argc < 1)
		return (builtin_env());
	if (argv[0][0] == '=' || array_len(argv) > 1)
		print_error(EXPORT, NULL, -1);
	i[1] = 0;
	while (argv[i[1]])
	{
		env = g_minishell.envp;
		newenv = create_new(argv[i[1]++]);
		i[0] = replace_existing(&newenv, &env);
		if (newenv && !env)
			add_at_index(&g_minishell.envp, newenv, i[0]);
	}
	return (EXIT_SUCCESS);
}
