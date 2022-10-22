/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:25:27 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/22 11:30:31 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n(char **argv)
{
	int		i;
	int		j;
	int		ctn;
	int		rtn;

	i = 0;
	rtn = 0;
	while (argv[i++])
	{
		j = 0;
		if (argv[i - 1][j++] == '-')
		{
			ctn = 0;
			while (argv[i - 1][j - 1])
			{
				if (argv[i - 1][j++ - 1] == 'n' && (rtn == i - 1))
					ctn = 1;
				else
					ctn = 0;
			}
			if (ctn)
				rtn++;
		}
	}
	return (rtn);
}

char	*delete_quotes(char *old_str)
{
	int		i;
	int		new_i;
	char	*new_str;

	i = 0;
	new_i = 0;
	new_str = (char *)ft_calloc(ft_strlen(old_str) + 1, sizeof(char));
	while (old_str[i])
	{
		while (old_str[i] == '\"' || old_str[i] == '\'')
			i++;
		new_str[new_i] = old_str[i];
		new_i++;
		i += (old_str[i] != '\0');
	}
	return (new_str);
}

int	builtin_echo(char **argv, int argc)
{
	int		i;
	char	**array;

	if (argc < 1)
		write(1, "", 0);
	if (argc < 2 && (argc > 0 && check_n(argv)))
		return (EXIT_SUCCESS);
	array = argv + check_n(argv);
	i = 0;
	while (array[i++])
	{
		if (i - 1 > 0)
			write(1, " ", 1);
		array[i - 1] = delete_quotes(array[i - 1]);
		write(1, array[i - 1], ft_strlen(array[i - 1]));
	}
	if (!(argc > 0 && check_n(argv)))
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
