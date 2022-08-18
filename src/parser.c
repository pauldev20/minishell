/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/18 09:41:38 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_input(char *input)
{
	char	**array;

	g_minishell.cmd_array = ft_split(input, ' ');
	array = g_minishell.cmd_array;
	while (*array)
	{
		builtin_parser(array);
		if (*array)
			array++;
	}
}
