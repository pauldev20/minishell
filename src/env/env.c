/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 22:21:41 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/22 00:45:52 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_at_index(t_env **list, t_env *el, int index)
{
	int		i;
	t_env	*env;
	t_env	*lst;

	i = 0;
	lst = (*list);
	while (i++ < index && lst)
	{
		env = lst;
		lst = lst->next;
	}
	el->next = lst;
	if (index > 0)
		env->next = el;
	else
		(*list) = el;
}

void	remove_at_index(t_env **list, int index)
{
	int		i;
	t_env	*env;
	t_env	*lst;

	i = 0;
	lst = (*list);
	while (i++ < index && lst)
	{
		env = lst;
		lst = lst->next;
	}
	free(lst->key);
	free(lst->value);
	if (index > 0)
		env->next = lst->next;
	else
		(*list) = lst->next;
	free(lst);
}

t_env	*parse_array_to_env(char **env, t_env *minienviro)
{
	int		i;
	char	**splitted;
	t_env	*enviro;
	t_env	*new;

	i = 0;
	enviro = minienviro;
	while (env[i])
	{
		splitted = ft_split(env[i++], '=');
		if (!in_list(enviro, splitted[0]))
		{
			new = (t_env *)malloc(sizeof(t_env));
			new->next = NULL;
			new->key = splitted[0];
			new->value = splitted[1];
			add_back(&enviro, new);
		}
		else
		{
			free(splitted[0]);
			free(splitted[1]);
		}
		free(splitted);
	}
	return (enviro);
}

void	print_env(t_env	*env)
{
	while (env)
	{
		if (env->value[0] == '\0')
			printf("%s=''\n", env->key);
		else
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
