/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:31:47 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/24 02:17:05 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arr(char **arr)
{
	for (int i = 0; arr[i] != NULL; i++)
		printf("ARR [%d]: %s\n", i, arr[i]);	
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
		return (0);
	else
		return (minishell(argv, envp));
	return (0);
}
