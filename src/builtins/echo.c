/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:25:27 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/19 10:34:46 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char **argv, int argc)
{
	int		i;
	char	**array;

	if (argc < 1)
		return ;
	array = argv + (argc > 1 && ft_strncmp(argv[0], "-n", 3) == 0);
	i = 0;
	while (array[i])
	{
		if (i > 0)
			printf(" ");
		printf("%s", array[i++]);
	}
	if (!(argc > 1 && ft_strncmp(argv[0], "-n", 3) == 0))
		printf("\n");
}
