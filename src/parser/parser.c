/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/08/24 18:54:27 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	*parse_input(char *input)
{
	char	**splitted;

	splitted = lexer(input, ' ');
	if (!splitted)
		return (print_error(QUOTE, NULL, 1));
	pipe_expander(&splitted);
	printf("{");
	for (int i = 0; splitted[i] != NULL; i++)
		printf("%s, ", splitted[i]);
	printf("NULL}\n");
	for (int i = 0; splitted[i] != NULL; i++)
		free(splitted[i]);
	free(splitted);
	return (NULL);
}
