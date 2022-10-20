/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:10:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/20 11:46:20 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arr_dup(char **enviroment)
{
	int		c;
	int		size;
	char	**envp;

	size = 0;
	while (enviroment[size] != NULL)
		size++;
	envp = (char **)malloc(sizeof(char *) * size);
	envp[size] = NULL;
	c = 0;
	while (c++ < size)
		envp[c - 1] = ft_strdup(enviroment[c - 1]);
	return (envp);
}

/*  RETURNS THE AMOUNT OF PIPES TO CHECK HOW MANY CMDS
	WILL BE ADDED TO PIPEX */
int	get_pipe_amount(char **tokens)
{
	int	pipe_counter;
	int	i;

	pipe_counter = 0;
	i = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strnstr(tokens[i], "PIPE", 4))
			pipe_counter++;
		i++;
	}
	return (pipe_counter);
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

char	**empty_arr(void)
{
	char	**arr;

	arr = ft_calloc(1, sizeof(char));
	return (arr);
}

bool	str_is_equal(char *str1, char *str2)
{
	return (ft_strcmp(str1, str2) == 0);
}
