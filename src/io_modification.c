/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_modification.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:14:26 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/13 16:32:15 by mhedtman         ###   ########.fr       */
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

int	get_outfile_fd(char *token, char *arr, int pipe)
{
	int	fd;
	int	i;

	fd = pipe;
	if (!token || !arr)
		return (fd);
	if (str_is_equal(token, "GREAT"))
		fd = open(arr, O_WRONLY | O_CREAT | O_TRUNC, 00700);
	else if (str_is_equal(token, "DGREAT"))
		fd = open(arr, O_WRONLY | O_CREAT | O_APPEND, 00700);
	return (fd);
}

int	get_infile_fd(t_execute_table *exe_table, char *token, char *arr, int pipe)
{
	int	fd;
	static int	here_doc;

	fd = pipe;
	if (!token || !arr)
		return (fd);
	if (str_is_equal(token, "LESS"))
		fd = open(arr, O_RDONLY, 0777);
	else if (str_is_equal(token, "DLESS"))
	{
		if (here_doc == 0)
		{
			here_doc_execute(exe_table, arr, exe_table->infiles);
			here_doc = 1;
		}
		fd = open("/tmp/here_doc", O_RDONLY, 0777);
		return (fd);
	}
	return (fd);
}
