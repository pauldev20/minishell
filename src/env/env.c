/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 22:21:41 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/20 23:40:04 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env_arr(t_env *list)
{
	int		i;
	int		v;
	char	**arr;
	char	*str;
	t_env	*lst;

	i = 0;
	lst = list;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	arr = ft_calloc(i + 1, sizeof(char *));
	v = 0;
	lst = list;
	while (lst)
	{
		str = ft_strjoin(lst->key, "=");
		arr[v] = ft_strjoin(str, lst->value);
		free(str);
		v++;
		lst = lst->next;
	}
	arr[v] = NULL;
	return (arr);
}

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
	t_env	*env;
	t_env	*lst;

	lst = *list;
	while (index-- && lst)
	{
		env = lst;
		lst = lst->next;
	}
	free(lst->key);
	free(lst->value);
	if (*list == lst)
		(*list) = lst->next;
	else
		env->next = lst->next;
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
