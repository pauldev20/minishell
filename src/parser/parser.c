/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/09/27 14:19:02 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

typedef struct s_cmd {
	char	**full_cmd;
	char	*full_path;
	int		infd;
	int		outfd;
}	t_cmd;

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->full_cmd = NULL;
	cmd->full_path = NULL;
	cmd->infd = STDIN_FILENO;
	cmd->outfd = STDOUT_FILENO;
	return (cmd);
}

void	*parse_input(char *input)
{
	char	**splitted;
	int		c;
	
	splitted = lexer(input, ' ');
	if (!splitted)
		return (print_error(QUOTE, NULL, 1));
	pipe_expander(&splitted);
	c = 0;
	while (splitted[c] != NULL)
	{
		splitted[c] = expand_vars(splitted[c]);
		c++;
	}
	handle_execute(splitted);
	// printf("{");
	// for (int i = 0; splitted[i] != NULL; i++)
	// 	printf("%s, ", splitted[i]);
	// printf("NULL}\n");
	for (int i = 0; splitted[i] != NULL; i++)
		free(splitted[i]);
	free(splitted);
	return (NULL);
}
