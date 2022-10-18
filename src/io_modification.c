/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_modification.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:14:26 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/18 16:22:56 by mhedtman         ###   ########.fr       */
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

	fd = STDOUT_FILENO;
	if (!token || !arr)
		return (pipe);
	else if (str_is_equal(token, "GREAT"))
		fd = open(arr, O_WRONLY | O_CREAT | O_TRUNC, 00700);
	else if (str_is_equal(token, "DGREAT"))
		fd = open(arr, O_RDWR | O_APPEND | O_CREAT, 00700);
	if (fd == -1)
		print_error(2, NULL, 1);
	return (fd);
}

int	get_infile_fd(t_exetable *exe_table, char *token, char *arr, int pipe)
{
	int			fd;
	static int	here_doc;

	fd = STDIN_FILENO;
	if (!token || !arr)
		return (pipe);
	else if (str_is_equal(token, "LESS"))
		fd = open(arr, O_RDONLY, 0777);
	else if (str_is_equal(token, "DLESS"))
	{
		if (here_doc == 0)
		{
			here_doc_execute(exe_table);
			here_doc = 1;
		}
		fd = open("/tmp/here_doc", O_RDONLY, 0777);
		if (fd == -1)
			print_error(2, NULL, 0);
		return (fd);
	}
	if (fd == -1)
		print_error(2, NULL, 1);
	return (fd);
}
