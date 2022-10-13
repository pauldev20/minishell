/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_modification.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:14:26 by mhedtman          #+#    #+#             */
/*   Updated: 2022/10/13 15:05:39 by mhedtman         ###   ########.fr       */
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
	printf("%d\n", fd);
	return (fd);
}

int	get_infile_fd(char *token, char *arr, int pipe)
{
	int	fd;

	fd = pipe;
	if (!token || !arr)
		return (fd);
	if (str_is_equal(token, "LESS"))
		fd = open(arr, O_RDONLY, 0777);
	else if (str_is_equal(token, "DLESS"))
	{
		here_doc_execute(arr, arr);
		fd = open("/tmp/here_doc", O_RDONLY, 0777);
		return (fd);
	}
	return (fd);
}
