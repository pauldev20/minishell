/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_modification.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:14:26 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/07 10:37:49 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*  CHECKS IF THE TOKEN PASSED AS AN ARG IS AN REDIRECTOR */
bool	is_input_redirector(char *str)
{
	if (ft_strnstr(str, "LESS", 4) || ft_strnstr(str, "DLESS", 5))
		return (true);
	return (false);
}

bool	is_output_redirector(char *str)
{
	if (ft_strnstr(str, "GREAT", 5) || ft_strnstr(str, "DGREAT", 6))
		return (true);
	return (false);
}

int	get_outfile_fd(char **token, char **arr)
{
	int	fd;
	int	i;

	fd = STDOUT_FILENO;
	i = -1;
	while (token[++i] != NULL)
	{
		if (is_output_redirector(token[i]))
		{
			if (ft_strnstr(token[i], "GREAT", 5))
				fd = open(arr[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 00700);
			else if (ft_strnstr(token[i], "DGREAT", 6))
				fd = open(arr[i + 1], O_WRONLY | O_CREAT | O_APPEND, 00700);
		}
	}
	return (fd);
}

int	get_infile_fd(char **token, char **arr)
{
	int	fd;
	int	i;

	fd = STDIN_FILENO;
	i = -1;
	while (token[++i] != NULL)
	{
		if (is_input_redirector(token[i]))
		{
			if (ft_strnstr(token[i], "LESS", 4))
				fd = open(arr[i + 1], O_RDONLY, 0777);
			else if (ft_strnstr(token[i], "DLESS", 5))
			{
				here_doc_execute(arr[i + 1], arr);
				fd = open("/tmp/here_doc", O_RDONLY, 0777);
				return (fd);
			}
		}
	}
	// i = -1;
	// while (token[++i] != NULL)
	// {
	// 	if (is_input_redirector(token[i]))
	// 	{
		
	// 	}
	// }
	return (fd);
}
