/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/24 10:00:44 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_input(char *input)
{
	char	**splitted;
	int		c;

	splitted = lexer(input, ' ');
	if (!splitted)
		return (NULL);
	pipe_expander(&splitted);
	c = 0;
	while (splitted[c] != NULL)
	{
		if (str_is_equal(splitted[0], "exit"))
		{
			if (splitted[1] == NULL)
				builtin_exit("0", NULL);
			else
				builtin_exit(splitted[1], splitted + 1);
		}
		splitted[c] = expand_vars(splitted[c]);
		c++;
	}
	return (splitted);
}
