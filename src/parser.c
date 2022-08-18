/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/18 08:59:24 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_cmds(char **cmd_arr)
{
	
}

void	parse_input(char *input)
{
	char	**array;

	g_minishell.cmd_array = ft_split(input, ' ');
	array = parse_cmds(g_minishell.cmd_array);
	while (*array)
	{
		builtin_parser(array);
		if (*array)
			array++;
	}
}
