/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:08:48 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/22 16:55:33 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_last(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
		env = env->next;
	return (env);
}

void	add_back(t_env **env, t_env *new)
{
	if (!env || !new)
		return ;
	if (!(*env))
		*env = new;
	else
		get_last(*env)->next = new;
}

int	set_env_var(t_env **env, char *key, char *value)
{
	t_env	*el;

	if (in_list(*env, key))
	{
		el = get_env_var(*env, key);
		if (!el)
			return (0);
		free(el->value);
		el->value = ft_strdup(value);
		return (1);
	}
	el = (t_env *)malloc(sizeof(t_env));
	if (!el)
		return (0);
	el->key = ft_strdup(key);
	el->value = ft_strdup(value);
	el->next = NULL;
	add_back(env, el);
	return (1);
}

t_env	*get_env_var(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	in_list(t_env *env, char *key)
{
	if (!key || !env)
		return (0);
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}
