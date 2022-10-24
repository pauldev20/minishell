/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:42:34 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/24 16:52:08 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_infile(char **cmd_array, char **token_array, int start, int stop)
{
	char	*infile;

	infile = NULL;
	while (start < stop)
	{
		if (str_is_equal(token_array[start], "INFILE"))
			infile = ft_strdup(cmd_array[start]);
		start++;
	}
	return (infile);
}

char	*get_outfile(char **cmd_array, char **token_array, int start, int stop)
{
	char	*outfile;
	int		create;

	outfile = NULL;
	while (start < stop)
	{
		if (str_is_equal(token_array[start], "OUTFILE"))
		{
			create = open(cmd_array[start], O_WRONLY | O_CREAT, 00700);
			outfile = ft_strdup(cmd_array[start]);
			close(create);
		}
		else if (str_is_equal(token_array[start], "WEIRDFILE"))
		{
			create = open(cmd_array[start], O_WRONLY | O_CREAT | O_TRUNC, 0700);
			close(create);
		}
		start++;
	}
	return (outfile);
}

char	*get_infile_type(char **token_array, int start, int stop)
{
	char	*infile;

	infile = NULL;
	while (start < stop)
	{
		if (str_is_equal(token_array[start], "DLESS"))
			infile = ft_strdup("DLESS");
		else if (str_is_equal(token_array[start], "LESS"))
			infile = ft_strdup("LESS");
		start++;
	}
	return (infile);
}

char	*get_outfile_type(char **token_array, int start, int stop)
{
	char	*outfile;

	outfile = NULL;
	while (start < stop)
	{
		if (str_is_equal(token_array[start], "GREAT"))
			outfile = ft_strdup("GREAT");
		else if (str_is_equal(token_array[start], "DGREAT"))
			outfile = ft_strdup("DGREAT");
		start++;
	}
	return (outfile);
}
