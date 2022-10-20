/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/20 23:53:54 by pgeeser          ###   ########.fr       */
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
				builtin_exit("0");
			else
				builtin_exit(splitted[1]);
		}
		splitted[c] = expand_vars(splitted[c]);
		c++;
	}
	return (splitted);
}
