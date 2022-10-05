/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:50:16 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/05 15:40:23 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arr(char **arr)
{
	for (int i = 0; arr[i] != NULL; i++)
		printf("ARR [%d]: %s\n", i, arr[i]);	
}

void print_token(char **splitted)
{
	printf("{");
	for (int i = 0; splitted[i] != NULL; i++)
		printf("%s, ", splitted[i]);
	printf("NULL}\n");
}

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
	c = 0;
	while (splitted[c])
	{
		if (ft_strnstr(splitted[c], "exit", 5))
			exit(0);
		c++;
	}
	start_execute(splitted);
	free_array(splitted);
	return (NULL);
}
