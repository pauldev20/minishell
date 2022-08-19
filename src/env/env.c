/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 22:21:41 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/19 12:05:36 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_at_index(t_env **list, t_env *el, int index)
{
	t_env	*env;

	env = (*list);
	while (index-- && (*list))
	{
		env = (*list);
		list = &(*list)->next;
	}
	el->next = (*list);
	env->next = el;
}

// void	remove_at_index(t_env **list, int index)
// {
// 	t_env	*env;
// 	t_env	*first;

// 	env = (*list);
// 	if (index == 0)
// 		first = (*list)->next;
// 	else
// 		first = (*list);
// 	while (index-- && (*list))
// 	{
// 		env = (*list);
// 		list = &(*list)->next;
// 	}
// 	free((*list)->key);
// 	free((*list)->value);
// 	if ((*list)->next)
// 		env->next = (*list)->next;
// 	else
// 		env->next = NULL;
// 	free((*list));
// }

void	remove_at_index(t_env **list, int index)
{
	int		i;
	t_env	*env;
	t_env	*lst;

	i = 0;
	env = (*list);
	lst = (*list);
	while (i++ < index && lst)
	{
		env = lst;
		lst = lst->next;
	}
	free(lst->key);
	free(lst->value);
	if ((*list)->next)
		env->next = (*list)->next;
	else
		env->next = NULL;
	free((*list));
}

t_env	*parse_array_to_env(char **env)
{
	int		i;
	char	**splitted;
	t_env	*enviro;
	t_env	*new;

	i = 0;
	enviro = NULL;
	while (env[i])
	{
		splitted = ft_split(env[i++], '=');
		new = (t_env *)malloc(sizeof(t_env));
		new->next = NULL;
		new->key = splitted[0];
		new->value = splitted[1];
		add_back(&enviro, new);
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
