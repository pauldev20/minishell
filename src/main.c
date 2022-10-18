/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:31:47 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/18 13:57:04 by mhedtman         ###   ########.fr       */
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
		return (minishell(argc, argv, envp));
	return (0);
}
