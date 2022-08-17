/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:10:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/17 20:11:19 by pgeeser          ###   ########.fr       */
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
