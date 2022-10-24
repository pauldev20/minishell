/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_modification.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgeeser <pgeeser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:22:32 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/24 03:20:05 by pgeeser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_token(char **arr, char **tokens, int i)
{
	if (str_is_equal(arr[i], "|"))
		return (ft_strdup("PIPE"));
	else if (str_is_equal(arr[i], "<"))
		return (ft_strdup("LESS"));
	else if (str_is_equal(arr[i], "<<"))
		return (ft_strdup("DLESS"));
	else if (str_is_equal(arr[i], "<>"))
		return (ft_strdup("WEIRDIO"));
	else if (str_is_equal(arr[i], ">"))
		return (ft_strdup("GREAT"));
	else if (str_is_equal(arr[i], ">>"))
		return (ft_strdup("DGREAT"));
	else if (i > 0 && (str_is_equal(tokens[i -1], "LESS")
			|| str_is_equal(tokens[i -1], "DLESS")))
		return (ft_strdup("INFILE"));
	else if (i > 0 && (str_is_equal(tokens[i -1], "GREAT")
			|| str_is_equal(tokens[i -1], "DGREAT")))
		return (ft_strdup("OUTFILE"));
	else if (i > 0 && (str_is_equal(tokens[i -1], "WEIRDIO")))
		return (ft_strdup("WEIRDFILE"));
	else
		return (ft_strdup("WORD"));
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
	tokens = (char **)ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (arr[i] != NULL)
	{
		tokens[i] = get_token(arr, tokens, i);
		i++;
	}
	return (tokens);
}

int	handle_empty_input(void)
{
	int	fd;

	fd = open("/tmp/empty_file", O_RDONLY | O_CREAT | O_TRUNC, 0777);
	return (fd);
}

char	**delete_doubles(char **arr, char **tokens)
{
	int	i;
	int	new_i;

	i = 0;
	new_i = 0;
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
	return (arr);
}
