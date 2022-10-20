/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:54:57 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/19 11:49:02 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

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
		env = create_new(argv[j++]);
		if (env)
			add_at_index(&g_minishell.envp, env, i++);
	}
	return (1);
}
