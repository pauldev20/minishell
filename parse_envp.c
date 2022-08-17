/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: max <max@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:25:10 by mhedtman          #+#    #+#             */
/*   Updated: 2022/08/17 20:19:12 by max              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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