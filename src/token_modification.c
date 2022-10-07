/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_modification.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:22:32 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/07 11:13:21 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  RETURNS THE AMOUNT OF PIPES TO CHECK HOW MANY CMDS
	WILL BE ADDED TO PIPEX */
int	get_pipe_amount(char **tokens)
{
	int	pipe_counter;
	int	i;

	pipe_counter = 0;
	i = 0;
	while (tokens[i] != NULL)
	{
		if (ft_strnstr(tokens[i], "PIPE", 4))
			pipe_counter++;
		i++;
	}
	return (pipe_counter);
}

/*  CREATES A TOKEN LIST TO KNOW WHAT WE ARE WORKING
	WITH [PIPES | REDIRECTOR | WORDS] */
char	**get_token_array(char **arr)
{
	char	**tokens;
	int		i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	tokens = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (arr[i] != NULL)
	{
		if (arr[i][0] == '|')
			tokens[i] = ft_strdup("PIPE");
		else if (arr[i][0] == '<')
		{
			if (arr[i][1] == '<')
				tokens[i] = ft_strdup("DLESS");
			else
				tokens[i] = ft_strdup("LESS");
		}
		else if (arr[i][0] == '>')
		{
			if (arr[i][1] == '>')
				tokens[i] = ft_strdup("DGREAT");
			else
				tokens[i] = ft_strdup("GREAT");
		}
		else
			tokens[i] = ft_strdup("WORD");
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

int	handle_empty_input(void)
{
	int	fd;

	fd = open("/tmp/empty_file", O_RDONLY | O_CREAT | O_TRUNC, 0777);
	return (fd);
}

/*  DELETES THE REDIRECTORS OUT OF THE STRING SO THAT 
	ONLY THE CMD PIPELINES REMAINS AND WE CAN ITERATE OVER IT */
char	**delete_io(char **arr, char **tokens, int *fd)
{
	int		i;
	int		new_i;

	new_i = 0;
	i = 0;
	while (tokens[i] != NULL)
	{
		while (tokens[i] != NULL && (is_input_redirector(tokens[i])
				|| is_output_redirector(tokens[i])))
			i += 2;
		arr[new_i] = arr[i];
		if (arr[new_i] == NULL)
			break ;
		new_i++;
		i++;
	}
	while (new_i < i)
	{
		arr[new_i] = NULL;
		new_i++;
	}
	if (arr[0] != NULL && arr[0][0] == '|')
	{
		new_i = 0;
		if (arr[0][0] == '|')
			*fd = handle_empty_input();
		while (arr[new_i] != NULL)
		{
			arr[new_i] = arr[new_i + 1];
			new_i++;
		}
	}
	return (arr);
}
