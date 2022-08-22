/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:25:27 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/20 16:42:21 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(char **argv, int argc)
{
	int		i;
	char	**array;

	if (argc < 2 && (argc > 0 && ft_strncmp(argv[0], "-n", 3) == 0))
		return (EXIT_SUCCESS);
	if (argc < 1)
		write(1, "", 1);
	array = argv + (argc > 0 && ft_strncmp(argv[0], "-n", 3) == 0);
	i = 0;
	while (array[i++])
	{
		if (i - 1 > 0)
			write(1, " ", 1);
		write(1, array[i - 1], ft_strlen(array[i - 1]));
	}
	if (!(argc > 0 && ft_strncmp(argv[0], "-n", 3) == 0))
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
