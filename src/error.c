/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedtman <mhedtman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:09:29 by pgeeser           #+#    #+#             */
/*   Updated: 2022/10/24 11:12:04 by mhedtman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(int errtype, char *params, int err)
{
	if (errtype == QUOTE)
		ft_putstr_fd("\033[31mminishell: error while parsing input\033[0m", 2);
	else if (errtype == BAD_FILE)
		ft_putstr_fd("\033[31mminishell: error while opening file\033[0m", 2);
	else if (errtype == CMD_NOT_FOUND)
		ft_putstr_fd("\033[31mminishell: command not found\033[0m", 2);
	else if (errtype == EXECUTE_ERROR)
		ft_putstr_fd("\033[31mminishell: error while executing file\033[0m", 2);
	else if (errtype == CD)
		ft_putstr_fd("\033[31mminishell: no such file or directory\033[0m", 2);
	else if (errtype == SYNTAX_PIPE)
		ft_putstr_fd("\033[31mminishell: syntax error near pipe\033[0m", 2);
	else if (errtype == SYNTAX_IO)
		ft_putstr_fd("\033[31mminishell: syntax error near io\033[0m", 2);
	else if (errtype == EXPORT)
		ft_putstr_fd("\033[31mminishell: wrong input for export\033[0m", 2);
	ft_putendl_fd(params, 2);
	if (err > -1)
		exit (err);
	g_minishell.exit_code = err * -1;
}
